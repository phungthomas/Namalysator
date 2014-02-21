#include "w_titlecheck.h"
#include "ui_w_titlecheck.h"
#include <fstream>
#include <sstream>
#include "metsparser.h"
#include "altoparser.h"
#include "w_structview.h"

const char *extract_title[] = {
	"HEADING"
	};


w_titlecheck::w_titlecheck(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::w_titlecheck)
{	
    m_ui->setupUi(this);
  
	m_ui->progressBar->reset();
	m_ui->tableWidget->setVisible(true);	
	m_ui->btnSave->setEnabled(false);
	m_ui->btnExport->setEnabled(true);
	createConnections();
	
	for (size_t i = 0; i < sizeof(extract_title) / sizeof(extract_title[0]); ++i)
	{
		to_extract.insert(extract_title[i]);
	}
	
}

w_titlecheck::~w_titlecheck()
{
    delete m_ui;
}

//!  //! create slots / signals
void w_titlecheck::createConnections()
{	   
	connect(m_ui->btnLoad,SIGNAL(clicked()),this,SLOT(load()));	
	connect(m_ui->btnSave,SIGNAL(clicked()),this,SLOT(save()));	
	connect(m_ui->btnExport,SIGNAL(clicked()),this,SLOT(exportData()));	
	connect(m_ui->btnReduceSize,SIGNAL(clicked()),this,SLOT(reduceSize()));
	connect(m_ui->btnOrginalSize,SIGNAL(clicked()),this,SLOT(originalSize()));	
} 
void w_titlecheck::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

//!set details of the batch
void w_titlecheck::setBatchDetail(const BatchDetail &d)
{ 	
	batchdetail = d; 
	db.setDataBaseName(batchdetail.database);  
}

void w_titlecheck::createArticle()
{	
	mapArticle.clear();
	mapArticleWithIdDiv.clear();
	int count =1;
	for (size_t i=0; i< vectItem.size(); i++)
	{	
		Article article;
		findBlockToArticle(vectItem[i], article.vectArticle);
		article.type = vectItem[i]->type;
		article.id = vectItem[i]->dmdId;
		article.title = vectItem[i]->label;		
		article.div = vectItem[i]->id;		
		mapArticle[vectItem[i]->counter] = article;
		mapArticleWithIdDiv[article.div] =article;
		count++;
	}
}

// Adds all blocks that are children of the given item to the array "output"
void w_titlecheck::findBlockToArticle(Item *item, std::vector<typeBlock> &output)
{
	for (size_t i=0; i< item->children.size();i++)
	{		
		Item *currentItem = &item->children[i];	
		if(currentItem->vectTypeBlock.size() >0)
		{
			for(size_t j=0;j< currentItem->vectTypeBlock.size();j++)
			{
				output.push_back(currentItem->vectTypeBlock[j]);
			}
		}
		findBlockToArticle(currentItem, output);			
	}
}

void w_titlecheck::createAltoDmd()
{
	blockAltoDmd.clear();
	std::pair<std::string,std::string> p;
	
	for (std::map<int,Article>::iterator it = mapArticle.begin(); it != mapArticle.end(); it++)
	{
		for (size_t i=0;i< it->second.vectArticle.size(); i++)
		{
		//	if (strcmp(p.second.c_str(),it->second.id.c_str())!= std::string::npos)
			{
				p.first = it->second.vectArticle[i].alto;
				p.second = it->second.id;
				blockAltoDmd.insert(p);
			}
		}		
	}	
}

void w_titlecheck::load()
{
	checktitle();	
	if (vTitle.size()>0)
	{
		updateSummaryTitleError();
		m_ui->btnSave->setEnabled(true);
		m_ui->btnExport->setEnabled(true);
	}
}



void w_titlecheck::checktitle()
{
	m_ui->btnExport->setEnabled(true);
	return;
	std::string currentAlto="";
	std::string currentTif="";

	vTitle = db.getvTitle(batchdetail.idTestSet);
	m_ui->progressBar->setRange(0,100);
	
	 for (size_t ij = 0;ij < vTitle.size(); ij++)
    {	
		Title t = vTitle[ij];	
		MetsFile mets = vTitle[ij].mets;
		std::string pathMets =  batchdetail.path + mets.path + "/" + mets.fileName;
		Item itemtree;
		Item *treeContents;
	    
		metsParser p(pathMets, &itemtree);
		ParseDocument(pathMets.c_str(),&p);
		treeContents = p.getItem();
		
		findArticle(treeContents);
		std::map<int, LinkedFiles> mapAltoPath;
		std::map<int, LinkedFiles> mapTiffPath;
		mapTiffPath = mets.mapLinked.find("IMGGRP")->second;
		mapAltoPath = mets.mapLinked.find("ALTOGRP")->second;
	    std::map<std::string,altoblock> mapAlto;
			
		m_ui->tableWidget->insertRow(ij);  	
		for(std::map<int,LinkedFiles>::iterator it = mapAltoPath.begin(); it != mapAltoPath.end(); it++)
		{
			int dpi = mapTiffPath[it->first].dpi;
			std::string path = batchdetail.path +"/"+ t.mets.path + it->second.fileName;
			altoparser ap(path,it->second,&mapAlto,dpi);	
			if (ParseDocument(path.c_str(),&ap)!=0)	
			{						
				QMessageBox::information(this, tr("Parse error"),
                                      tr("Could not parse %1.").arg(it->second.fileId.c_str()));				
			}
			else
			{							
					mapAlto[it->second.fileId]=ap.getAltoBlock();
			}		
		}
		
		createArticle();
		
		int row=0;
		QImage image,originImage;
		std::string path;	
	
		Article a = mapArticleWithIdDiv.find(vTitle[ij].article.div)->second;
		bool found = false;	
		for (size_t i =0;i< a.vectArticle.size();i++)
		{		
			if (to_extract.find(a.vectArticle[i].type)!= to_extract.end())			
			{
				for (std::map<int,LinkedFiles>::iterator it = mapAltoPath.begin(); it != mapAltoPath.end(); it++)
				{ 				
					{
						if (it->second.fileId == a.vectArticle[i].alto)
						{						
							currentTif = mapTiffPath.find(it->first)->second.fileName;
							currentAlto = it->second.fileId;
					
							path = batchdetail.path + mets.path + currentTif;							
							found =true;
							originImage.load(path.c_str());	
							break;
						}						
					}	
				}
				QString ss = QString::fromUtf8(a.title.c_str());
				QTableWidgetItem *title = new QTableWidgetItem(ss,0);		
				altoblock at = mapAlto[a.vectArticle[i].alto];	
				
				at.mapalto.find(a.vectArticle[i].block);
					if (at.mapalto.find(a.vectArticle[i].block) != at.mapalto.end())
						{
							Block block = at.mapalto[a.vectArticle[i].block];						
					
					int x = block.vpos;
					int y = block.hpos;
					int width = block.width;
					int height =  block.height;						
					image = originImage.copy(x,y,width,height);	
					vImage.push_back(image);
					QString ss;
					QTableWidgetItem *item;
					
					item  = new QTableWidgetItem(ss.setNum(t.countString),t.id);
					m_ui->tableWidget->setItem(ij,1,item);		
					if (t.countError !=0)
					{					
						item  = new QTableWidgetItem(ss.setNum(t.countError),t.id);	
					}
					else
						item  = new QTableWidgetItem("",t.id);	
					
					m_ui->tableWidget->setItem(ij,2,item);		
					m_ui->tableWidget->setItem(ij,0,title);								
					row++;		
					}			
				i= a.vectArticle.size();
			}		
		}
	
		float val = float(ij) /vTitle.size() *100; 	
		m_ui->progressBar->setValue(int(val));		
	}
	
	for (size_t i=0; i< vImage.size();i++)
		{
			QLabel *label = new QLabel;		
			label->setPixmap(QPixmap::fromImage(vImage[i]));
			m_ui->tableWidget->setCellWidget(i,3,label);
		
		}
	m_ui->progressBar->setVisible(false);
	m_ui->tableWidget->resizeColumnsToContents();
	m_ui->tableWidget->resizeRowsToContents();
	m_ui->tableWidget->setVisible(true);
	m_ui->btnLoad->setEnabled(false);
	m_ui->lbWait->setVisible(false);
}


void w_titlecheck::findArticle(Item *item)
{
	for (size_t i=0; i< item->children.size();i++)
	{		
		Item *currentItem = &item->children[i];
		if(currentItem->dmdId.find("MODSMD")== 0)
		{	
			vectItem.push_back(currentItem);
		}
		findArticle(currentItem);
	}

}

void w_titlecheck::save()
{	
	for (int i=0; i < m_ui->tableWidget->rowCount(); i++)
	{
		int id = m_ui->tableWidget->item(i,2)->type();
		std::string error = m_ui->tableWidget->item(i,2)->text().toStdString();
		if (error !="")
		{
			db.updateTitleError(id,atoi(error.c_str()));
		}	
	}
	updateSummaryTitleError();
}

void w_titlecheck::updateSummaryTitleError()
{
	std::pair<int,int> pair = db.getSumCharacter(batchdetail.idTestSet);
	QString ss;
	m_ui->lbTotal->setText(ss.setNum(pair.first));
	m_ui->lbError->setText(ss.setNum(pair.second));
	float percentage = float(pair.second) /float (pair.first) * 100;
	percentage = 100 -percentage;
	char tmp[20];
	sprintf_s(tmp, "%.2f", percentage);
	m_ui->lbPercentage->setText(tmp);
	
}

void w_titlecheck::reduceSize()
{
	for (int i=0; i < m_ui->tableWidget->rowCount(); i++)
	{		
		QImage image = vImage[i];
		image = image.scaled(image.width() /2 , image.height() /2);
		QLabel *label = new QLabel;		
		label->setPixmap(QPixmap::fromImage(image));
		m_ui->tableWidget->setCellWidget(i,3,label);	
	}
	m_ui->tableWidget->resizeRowsToContents();
	m_ui->tableWidget->resizeColumnsToContents();

}

void w_titlecheck::originalSize()
{
	for (int i=0; i < m_ui->tableWidget->rowCount(); i++)
	{	QImage image = vImage[i];	
		QLabel *label = new QLabel;		
		label->setPixmap(QPixmap::fromImage(image));
		m_ui->tableWidget->setCellWidget(i,3,label);
	}	
	m_ui->tableWidget->resizeRowsToContents();
	m_ui->tableWidget->resizeColumnsToContents();
}

// #define EXTERNAL_TIMING

void w_titlecheck::exportData()
{

	QString fileName = QFileDialog::getSaveFileName(this,tr("Open File"),"",tr("file (*.ods)"));
    std::string message;
     if (!fileName.isEmpty()) 
     {		
		  message = fileName.toStdString();
     }

	headcutter *hc = 0;
	hc = new headcutter;
	hc->open_document(message);
	std::string currentAlto="";
	std::string currentTif="";
	std::vector<Title> vTitle = db.getvTitle(batchdetail.idTestSet);

	for (size_t ij = 0;ij < vTitle.size(); ij++)
    {	
		// prepare for a new METS file
		// Clear the list of DIVs with a DMDID
		vectItem.clear();
		const Title &t = vTitle[ij];	
		const MetsFile &mets = vTitle[ij].mets;
		std::string pathMets =  batchdetail.path + mets.path + "/" + mets.fileName;
		Item itemtree;
		Item *treeContents;

		metsParser p(pathMets, &itemtree);
		ParseDocument(pathMets.c_str(),&p);
		treeContents = p.getItem();
		
		std::map<int,LinkedFiles> mapAltoPath;
		std::map<int,LinkedFiles> mapTiffPath;
		mapTiffPath = mets.mapLinked.find("IMGGRP")->second;
		mapAltoPath = mets.mapLinked.find("ALTOGRP")->second;
		findArticle(treeContents);		
	    std::map<std::string,altoblock> mapAlto;

		for(std::map<int,LinkedFiles>::iterator it = mapAltoPath.begin(); it != mapAltoPath.end(); it++)
		{
			int dpi = mapTiffPath[it->first].dpi;
			std::string path = batchdetail.path +"/"+ t.mets.path + it->second.fileName;
			altoparser ap(path,it->second, &mapAlto, dpi);	
			if (ParseDocument(path.c_str(),&ap)!=0)
			{
					// print error				
			}
			else
			{
					mapAlto[it->second.fileId] = ap.getAltoBlock();
			}
		}
		createArticle();		
		std::string path;
		Article a = mapArticleWithIdDiv.find(vTitle[ij].article.div)->second;
		bool found = false;	
		for (size_t i =0;i < a.vectArticle.size();i++)
		{
			if ((a.vectArticle[i].type == "HEADING") ||(a.vectArticle[i].type == "CAPTION") )
			{
				for (std::map<int,LinkedFiles>::iterator it = mapAltoPath.begin(); it != mapAltoPath.end(); it++)
				{
					if (it->second.fileId == a.vectArticle[i].alto)
					{
						currentTif = mapTiffPath.find(it->first)->second.fileName;
						currentAlto = it->second.fileId;
						path = batchdetail.path + mets.path + currentTif;
						found = true;
						break;
					}
				}
				altoblock at = mapAlto[a.vectArticle[i].alto];					
				at.mapalto.find(a.vectArticle[i].block);
				if (at.mapalto.find(a.vectArticle[i].block) != at.mapalto.end())
					{
						Block block = at.mapalto[a.vectArticle[i].block];						
						hc->cut_headings(path,currentAlto,block,a.title);					
					}	
			
				i= a.vectArticle.size();
			}		
		}	
	}	
	hc->close_document();
	QMessageBox::information(this, tr("Namalysator"),
                                   tr("Export finished"));	
}