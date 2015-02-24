#include "qwidgettaberror.h"
#include <stdio.h>
#include <windows.h>
#include "codeeditor.h"
#include <QFile>
#include <QMessageBox>
#include <fstream>
tabErrors::tabErrors(int id, BatchDetail &bd):batch(bd)
{
	id_cat = id;
	db.setDataBaseName(batch.database);  
	vSchemaE = db.getvErrorPerCategory(id_cat,batch.idTestSet);
	labels  << tr("Severity") << tr("Error Category") << tr("Location")<<tr("Message") << tr("File") << tr("Year")<<tr("Accepted");// << tr("Number of issues");
	editor = new CodeEditor();
	plainTextEdit = new QPlainTextEdit();	
	btnNext = new QPushButton("Next");
	table = new QTableWidget();
	fillTableError(vSchemaE);
	comboError = new QComboBox();
	comboYear = new QComboBox();

	search_item = "";	
	fillCombo(id_cat,batch);
	createConnections();
	QSplitter *splitter = new QSplitter(Qt::Vertical,this);
	splitter->addWidget(table);
	splitter->addWidget(editor);	
	QGridLayout *grid = new QGridLayout();		 
	grid->addWidget(splitter, 0, 0);
	grid->addWidget(btnNext, 2, 0);
	grid->setColumnStretch(0, 10);
	this->setLayout(grid);

}

void tabErrors::createConnections()
{
	connect(comboError, SIGNAL(currentIndexChanged(QString)),this, SLOT(getcbCategory(QString)));
	connect(table,SIGNAL(cellClicked(int,int)),this,SLOT(lineChanged(int,int)));
	connect(comboYear,SIGNAL(currentIndexChanged(QString)),this, SLOT(getcbYear(QString)));	
	connect(btnNext,SIGNAL(clicked()),this,SLOT(findNext()));
}

void tabErrors::getcbCategory(QString errortype)
{	
	vSchemaE =db.getErrorFilter(errortype.toStdString(),batch.idTestSet,id_cat);	
	if(comboYear->currentText()=="")
	{
		fillTableError(vSchemaE);
	}
	else
	{
		std::vector<MetsError> vTemp;
		for(size_t i =0;i < vSchemaE.size();i++)
		{
			if (vSchemaE[i].mets.year == comboYear->currentText().toInt())
			{
				vTemp.push_back(vSchemaE[i]);
			}	
		}	
		fillTableError(vTemp);			
	}	
}


void tabErrors::getcbYear(QString cbyear)
{	
	vSchemaE = db.getErrorFilter(comboError->currentText().toStdString(),batch.idTestSet,id_cat);	
	if(cbyear=="")
	{
		fillTableError(vSchemaE);
	}
	else
	{
		std::vector<MetsError> vTemp;
		for(size_t i =0;i < vSchemaE.size();i++)
		{
			if (vSchemaE[i].mets.year == cbyear.toInt())
			{
				vTemp.push_back(vSchemaE[i]);
			}	
		}	
		fillTableError(vTemp);		
	}
}

//TODO changer lineChanged
void tabErrors::lineChanged(int row,int col)
{
	editor->clear();

	btnNext->setEnabled(false);
	if ((col !=06) && (row!= 0))
	{
		std::string link;
		MetsError s = vSchemaE[row-1];

		if (s.relatedType == "METS")
		{				
			link = batch.path + s.mets.path + "/" + s.mets.fileName ;	
		}
		else
		{		
			link = batch.path +  s.mets.path +s.linkedFiles.fileName ;
		}		


		QFile file(link.c_str());
		if (file.open(QIODevice::ReadOnly))
			editor->setPlainText(file.readAll());

		findLine(batch, s);
		//	ShellExecuteA(NULL, "open",link.c_str(), NULL, NULL, SW_SHOWNORMAL);
	}

}

void tabErrors::fillTableError(std::vector<MetsError> vError)
{

	table->setColumnCount(labels.size());
	table->setRowCount(vError.size()+1);		
	table->setEditTriggers(false);
	table->setHorizontalHeaderLabels(labels);
	table->setAlternatingRowColors(true);
	table->setShowGrid(true);
	table->verticalHeader()->hide();
	table->setRowHeight(0,20);
	for (int i=0;i<table->rowCount();i++)
	{
		table->setRowHeight(i,20);
	}
	for (int i=0;i<table->columnCount();i++)
	{
		table->setColumnWidth(i,100);		
	}	

	for( size_t i=0;i < vError.size(); i++)
	{
		QString ss ;	
		newItem = new QTableWidgetItem(vError[i].errorType.severity.gravity.c_str(),i);		
		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(i+1, 0, newItem);

		newItem = new QTableWidgetItem(vError[i].errorType.error.c_str(),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(i+1, 1, newItem);

		newItem = new QTableWidgetItem(vError[i].filePart.c_str(),i);
		//		newItem = new QTableWidgetItem(ss.setNum(vError[i].errorLine),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(i+1, 2, newItem);

		newItem = new QTableWidgetItem(vError[i].message.c_str(),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(i+1, 3, newItem);		



		if (vSchemaE[i].relatedType == "METS")
		{
			newItem = new QTableWidgetItem(vError[i].mets.fileName.c_str(),i);			
		}
		else
		{
			newItem = new QTableWidgetItem(vError[i].linkedFiles.fileName.c_str(),i);
		}

		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(i+1, 4, newItem);

		newItem = new QTableWidgetItem(ss.setNum(vError[i].mets.year),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(i+1, 5, newItem);
		
		QCheckBox* checkBox = new QCheckBox();
		table->setCellWidget(i+1, 6,checkBox);
	}
	table->resizeColumnsToContents();
	for (int i=0;i<table->columnCount();i++)
	{
		if (table->columnWidth(i) <100)
		{
			table->setColumnWidth(i,100);		
		}				
	}
}
//! changer nom combo
void tabErrors::fillCombo(int id_cat,const BatchDetail &batch)
{
	std::vector<ErrorType> v = db.getDistinctErrorType(id_cat,batch.idTestSet);
	comboError->addItem("");	
	for (size_t i = 0;i < v.size();i++)
	{
		comboError->addItem(v[i].error.c_str());	
	}	

	std::map<int,std::pair<int,int>> m = db.getSumMetsYear(batch.idTestSet);
	comboYear->addItem("");
	for (std::map<int,std::pair<int,int>>::iterator it = m.begin(); it!= m.end();it++)
	{
		QString ss;
		comboYear->addItem(ss.setNum(it->first));
	}
	table->setCellWidget(0,1,comboError);
	table->setCellWidget(0,5,comboYear);
}

int tabErrors::getSizeVError()
{
	return vSchemaE.size();
}

void tabErrors::findLine(const BatchDetail &batch,MetsError s)
{	
	std::string link = batch.path + s.mets.path + "/" + s.mets.fileName ;	
	editor->setCenterOnScroll(true);	
	if (s.errorType.id == cat_schema_err)
	{
		ifstream myfile;		
		myfile.open (link.c_str());		
		if(myfile.fail())
		{			
			myfile.close(); 			
			QMessageBox::information(this, tr("Path error"),
				tr("Cannot load %1.").arg(link.c_str()));		
		}
		else
		{	
			int count=0;
			std::string line;
			while (!myfile.eof())
			{	
				count++;
				getline(myfile,line);	
				if ( count == s.errorLine)
				{
					search_item = line;
				}					
			}
			myfile.close(); 
		}
	}
	else
	{
		search_item = (s.id_search);	
	}   
	editor->find(search_item.c_str());

	if (s.errorType.id == cat_multipleBlock)
	{
		btnNext->setEnabled(true);
	} 	 
}


void tabErrors::findNext()
{
	editor->find(search_item.c_str());
}