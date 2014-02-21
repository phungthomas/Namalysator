#include "w_disk.h"
#include "ui_w_disk.h"
#include "dbrequest.h"
#include "sstream"
#include <stdio.h>
#include <windows.h>
#include "tiffio.h"
#include "calendarcommons.h"
#include "precisiontimer.h"

w_disk::w_disk(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::w_disk)
{		
    m_ui->setupUi(this); 
    m_ui->scrollAreaHeader->setWidget(m_ui->lblHeader);
    createConnections();    
}   

void w_disk::createConnections()
{
	connect(m_ui->calendarWidget,SIGNAL(clicked(QDate)),this,SLOT(clickDate(QDate)));
    connect(m_ui->treeViewMets,SIGNAL(doubleClicked(QModelIndex)),this, SLOT(openPath(QModelIndex)));  
    connect(m_ui->listMets,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(getIdMets(QListWidgetItem*)));
}

w_disk::~w_disk()
{
    delete m_ui;
}
/// <summary>set detail of the batch</summary>
/// <param name="d">Batch</param>
void w_disk::setBatchDetail(const BatchDetail &d)
{ 
	batch = d; 	
	db.setDataBaseName(batch.database);
	loadYear(m_ui->tableYear, batch);
	initCalendarWidget(m_ui->calendarWidget,batch);	
}

void w_disk::changeEvent(QEvent *e)
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
///<summary> get mets when click calendar</summary>
void w_disk::clickDate(QDate search)
{
	clearDetails();			
	m_ui->treeViewMets->setModel(&model);
#ifdef LOG_TIMING
	precisiontimer pt(g_pool.getConnection(batch.database).fpLog);
#endif
	
	// TODO : handle several issues on same day
	bool findfirst=false;
	std::vector<MetsFile> result;
#ifdef LOG_TIMING
	pt.Start();
#endif
	if (batch.getMetsByDate(search, result)) {
#ifdef LOG_TIMING
		pt.LogTime("w_disk::clickDate - batch.getMetsByDate");
#endif
		listOfMetsOnDay.clear();
		for (std::vector<MetsFile>::const_iterator it = result.begin(); it != result.end(); it++) {
			listOfMetsOnDay[it->idMets] = *it;

			std::stringstream sPath;
			sPath << batch.path << it->path;
			lst = new QListWidgetItem(it->fileName.c_str(), m_ui->listMets, it->idMets);
			if (findfirst == false)
			{
				m_ui->treeViewMets->setRootIndex(model.index(sPath.str().c_str()));
#ifdef LOG_TIMING
				pt.LogTime("w_disk::clickDate - m_ui->treeViewMets->setRootIndex");
#endif
				if (initHeader(*it)==true)
				{
#ifdef LOG_TIMING
					pt.LogTime("w_disk::clickDate - initHeader");
#endif
					m_ui->treeViewMets->expandAll();
#ifdef LOG_TIMING
					pt.LogTime("w_disk::clickDate - m_ui->treeViewMets->expandAll");
#endif
				}
				initDetails(*it);
#ifdef LOG_TIMING
				pt.LogTime("w_disk::clickDate - initDetails");
#endif
				findfirst = true;
			}
		}
		m_ui->treeViewMets->resizeColumnToContents(0);
		m_ui->treeViewMets->resizeColumnToContents(1);
		m_ui->treeViewMets->resizeColumnToContents(2);
		m_ui->treeViewMets->resizeColumnToContents(3);
		
		for (size_t i =0; i< 4;i++)
		{
			if (m_ui->treeViewMets->columnWidth(i) < 100)
			{
				m_ui->treeViewMets->setColumnWidth(i,100);
			}	
		}
#ifdef LOG_TIMING
		pt.LogTime("w_disk::clickDate - various UI operations");
#endif
	}
	else
	{
	
	}		
}

void w_disk::openPath(QModelIndex index)
{
	std::string path = model.filePath(index).toStdString();
	ShellExecuteA(NULL, "open",path.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
///<summary> load the header of current Mets</summary>
bool w_disk::initHeader(const MetsFile &mets)
{
	std::map<int,LinkedFiles> tifPath = db.getMapLinkedFiles(mets.idMets,"IMGGRP");	
	std::string path = batch.path  + mets.path + "" + tifPath[1].fileName;
	QImage image(path.c_str());	
	if (image.isNull()) {
		QMessageBox::information(this, tr("Header"),
                                      tr("Cannot load %1.").arg(path.c_str()));
        return false;
	}
	else  
	{		
		image = image.scaled(900,1300);
		image = image.copy(0,0,900,400);
		m_ui->lblHeader->setPixmap(QPixmap::fromImage(image));
		m_ui->scrollAreaHeader->setWidgetResizable(true);
	}
	return true;
}

void w_disk::initDetails(const MetsFile &mets)
{
	m_ui->lbFileName->setText(mets.fileName.c_str());
	m_ui->lbIssueNumber->setText(QString::fromUtf8(mets.issueNumber.c_str()));	
	std::stringstream ss;
	for(size_t i =0;i< mets.vectIssueNumber.size();i++)
	{
		ss << mets.vectIssueNumber[i];
		if (mets.vectIssueNumber.size() > i+1)
		ss << " , ";
	}
	m_ui->lbIssueParsed->setText(ss.str().c_str());
	m_ui->lbPages->setNum(mets.pages);
	if (!mets.supplements.empty()) {
		for (std::vector<std::string>::const_iterator it = mets.supplements.begin(); it != mets.supplements.end(); ++it) {
			new QListWidgetItem(QString::fromUtf8(it->c_str()), m_ui->listSupplement, 0);
		}
	}
}

void w_disk::getIdMets(QListWidgetItem* item)
{
#ifdef LOG_TIMING
	precisiontimer pt(g_pool.getConnection(batch.database).fpLog);
#endif
	std::stringstream sPath;
	MetsFile mets;
#ifdef LOG_TIMING
	pt.Start();
#endif
	if (batch.getMetsByID(item->type(), mets)) {
#ifdef LOG_TIMING
		pt.LogTime("w_disk::getIdMets - batch.getMetsByID");
#endif
		sPath << batch.path << "/" << mets.path;
		m_ui->treeViewMets->setModel(&model);
#ifdef LOG_TIMING
		pt.LogTime("w_disk::getIdMets - m_ui->treeViewMets->setModel");
#endif
		m_ui->treeViewMets->setRootIndex(model.index(sPath.str().c_str()));
#ifdef LOG_TIMING
		pt.LogTime("w_disk::getIdMets - m_ui->treeViewMets->setRootIndex");
#endif
		initHeader(mets);
#ifdef LOG_TIMING
		pt.LogTime("w_disk::getIdMets - initHeader");
#endif
		initDetails(mets);
#ifdef LOG_TIMING
		pt.LogTime("w_disk::getIdMets - initDetails");
#endif
		m_ui->treeViewMets->expandAll();
#ifdef LOG_TIMING
		pt.LogTime("w_disk::getIdMets - m_ui->treeViewMets->expandAll");
#endif
	} else {
		QMessageBox::information(this, tr("w_disk::getIdMets"), tr("Could not get METS with this ID"));
	}
}


void w_disk::clearDetails()
{
	m_ui->listMets->clear();
	m_ui->listSupplement->clear();
	m_ui->lbFileName->setText("No issue selected");
	m_ui->lbIssueNumber->setText("No issue selected");	
	m_ui->lbIssueParsed->setText("No issue selected");
	m_ui->lbPages->setText("No issue selected");		
	m_ui->lblHeader->clear();
	m_ui->treeViewMets->setModel(NULL);
}