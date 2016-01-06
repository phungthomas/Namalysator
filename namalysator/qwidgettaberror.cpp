#include "qwidgettaberror.h"
#include <stdio.h>
#include <windows.h>
#include "codeeditor.h"
#include <QFile>
#include <QMessageBox>
#include <fstream>
#include "w_accepted.h"
#include <QLabel>

tabErrors::tabErrors(int id,std::vector<MetsError>* v, BatchDetail &bd,DialogImage* dialogTab):batch(bd),dial(dialogTab)
{
	id_cat = id;
	db.setDataBaseName(batch.database);  
	vSchemaE = v;
	labels  <<tr("Accepted")<< tr("Severity") << tr("Error Category") << tr("Location")<<tr("Message") << tr("File") << tr("Year")<<tr("METS Filename");// << tr("Number of issues");
	editor = new CodeEditor();
	//plainTextEdit = new QPlainTextEdit();	
	btnNext = new QPushButton("Next");
	table = new QTableWidget();
	fillTableError(vSchemaE);
	comboError = new QComboBox();
	comboYear = new QComboBox();

	search_item = "";	
	fillCombo();
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
	connect(comboError, SIGNAL(currentIndexChanged(int)),this, SLOT(getcbCategory(int)));
	connect(table,SIGNAL(cellClicked(int,int)),this,SLOT(lineChanged(int,int)));
	connect(table,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(lineChanged(int,int,int,int)));
	connect(comboYear,SIGNAL(currentIndexChanged(int)),this, SLOT(getcbYear(int)));	
	connect(btnNext,SIGNAL(clicked()),this,SLOT(findNext()));
}

void tabErrors::getcbCategory(int errortype)
{	
	//(*vSchemaE) =db.getErrorFilter(errortype.toStdString(),batch.idTestSet,id_cat);

	QVariant data = comboError->itemData(errortype);
	int compInt = data.toInt();
	
	if(compInt == -1)
	{
		fillTableError(vSchemaE);
	}
	else
	{
		vTemp.clear();
		for(size_t i =0;i < (*vSchemaE).size();i++)
		{
			if ((*vSchemaE)[i].errorType.id_type == compInt)
			{
				vTemp.push_back((*vSchemaE)[i]);
			}	
		}	
		fillTableError(&vTemp);			
	}	
}


void tabErrors::getcbYear(int cbyear)
{	
	//*vSchemaE = db.getErrorFilter(comboError->currentText().toStdString(),batch.idTestSet,id_cat);

	QVariant year = comboYear->itemData(cbyear);
	int compInt = year.toInt();
	if(compInt==-1)
	{
		fillTableError(vSchemaE);
	}
	else
	{
		vTemp.clear();
		for(size_t i =0;i < vSchemaE->size();i++)
		{
			if ((*vSchemaE)[i].mets.year == compInt)
			{
				vTemp.push_back((*vSchemaE)[i]);
			}	
		}	
		fillTableError(&vTemp);		
	}
}

void tabErrors::lineChanged(int row,int col,int,int){
	if ( col == 5 ){
		lineChanged(row,col);
	}
}

//TODO changer lineChanged
void tabErrors::lineChanged(int row,int col)
{
	editor->clear();

	btnNext->setEnabled(false);
	if ((col !=0) && (row!= 0))
	{
		std::string link;
		MetsError s = (*workingE)[row-1];

		link = batch.path + s.filenameFullPath;	


		QFile file(link.c_str());
		if (file.open(QIODevice::ReadOnly))
			editor->setPlainText(QString::fromUtf8(file.readAll()));

		findLine(batch, s);
		std::string filename  = s.filenameShort;
		
		if ( filename.size()!=0 ){
			std::string str=link;
			std::string rep="/png/";
			str = str.replace(str.end()-4,str.end(),".png",4);
			std::size_t it = str.find("/alto/");
			str = str.replace(it,6,rep);
			QImage icon;
			icon.load(str.c_str());

			dial->setQImage ( icon );


			
		}
		//	ShellExecuteA(NULL, "open",link.c_str(), NULL, NULL, SW_SHOWNORMAL);
	}

}

void tabErrors::fillTableError(std::vector<MetsError>* vError)
{
	workingE = vError;
	table->setColumnCount(labels.size());
	table->setRowCount(vError->size()+1);		
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

	for( size_t i=0;i < vError->size(); i++)
	{
		QString ss;	
		int col = 0;

		acceptedW* checkBox = new acceptedW((*vError)[i].accepted,(*vError)[i].hashkey);
		table->setCellWidget(i+1, col++,checkBox);
		connect ( checkBox, SIGNAL(changeHash(bool,std::string)), this, SLOT(accepted(bool,std::string)));

		newItem = new QTableWidgetItem((*vError)[i].errorType.severity.gravity.c_str(),i);		
		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(i+1, col++, newItem);

		newItem = new QTableWidgetItem((*vError)[i].errorType.error.c_str(),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(i+1, col++, newItem);

		newItem = new QTableWidgetItem((*vError)[i].filePart.c_str(),i);
		//		newItem = new QTableWidgetItem(ss.setNum(vError[i].errorLine),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(i+1, col++, newItem);

		newItem = new QTableWidgetItem(QString::fromUtf8((*vError)[i].message.c_str()),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(i+1, col++, newItem);		

		newItem = new QTableWidgetItem((*vError)[i].filenameShort.c_str(),i);

		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(i+1,col++, newItem);

		newItem = new QTableWidgetItem(ss.setNum((*vError)[i].mets.year),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(i+1,col++, newItem);

		newItem = new QTableWidgetItem((*vError)[i].mets.fileName.c_str(),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(i+1,col++, newItem);
		

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
void tabErrors::fillCombo()
{

	comboError->addItem("",QVariant(-1));
	comboYear->addItem("",QVariant(-1));

	std::set<int> cats;
	std::set<int> valyear;
	
	for ( size_t i=0; i < (*vSchemaE).size();i++){
		int errT = (*vSchemaE)[i].errorType.id_type;
		;
		if (cats.find(errT) == cats.end()){
			cats.insert(errT);
			comboError->addItem((*vSchemaE)[i].errorType.error.c_str(),QVariant(errT));
		}
		int year = (*vSchemaE)[i].mets.year;
		if ( valyear.find(year)==valyear.end()){
			valyear.insert(year);
			QString ss;
			comboYear->addItem(ss.setNum(year),QVariant(year));
		}
	}
	
	table->setCellWidget(0,2,comboError);
	table->setCellWidget(0,6,comboYear);
}

int tabErrors::getSizeVError()
{
	return (*vSchemaE).size();
}

void tabErrors::findLine(const BatchDetail &batch,MetsError s)
{	
	std::string link = batch.path + s.filenameFullPath ;	
	editor->setCenterOnScroll(true);	
	if (s.errorType.id == cat_schema_err || s.errorLine != 0 )
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
	if (editor->find(QString::fromUtf8(search_item.c_str()))){
		btnNext->setEnabled(true);
	};	 
}


void tabErrors::findNext()
{
	if (!editor->find(QString::fromUtf8(search_item.c_str()))){
		btnNext->setEnabled(false);
	};
}

void tabErrors::accepted(bool val,std::string hashkey){
	if ( val) {
		db.insertAccepted(hashkey);	
	}else{
		db.deleteAccepted(hashkey);
	}
}