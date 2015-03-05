#include "dateerrortab.h"
#include <stdio.h>
#include <windows.h>
#include <sstream>
#include <QDate>
#include "w_accepted.h"

dateerrortab::dateerrortab(int id):batchDetail(BatchDetail::getBatchDetail())
{
	id_cat = id;
	db.setDataBaseName(batchDetail.database);  

// 	vSchemaE = db.getvErrorPerCategory(id_cat,batchDetail.idTestSet);


	labels  << tr("Accepted") << tr("Severity") << tr("Error Category") <<tr("Message") <<tr ("Year"); //<< tr("Date Begin") << tr("Date End"); //<< tr("Year");
	
	vDateError = db.getDateError(batchDetail.idTestSet);	
	table = new QTableWidget();
	fillTableError(vDateError);
	comboError = new QComboBox();
	comboYear = new QComboBox();	
	fillCombo(id_cat,batchDetail);
    connect(comboError, SIGNAL(currentIndexChanged(QString)),this, SLOT(getcbCategory(QString)));
  //  connect(table,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(getLine(int,int)));
    connect(comboYear,SIGNAL(currentIndexChanged(QString)),this, SLOT(getcbYear(QString)));	
}

void dateerrortab::getcbCategory(QString errortype)
{
	std::vector<DateError> vTemp;
	if(errortype=="")
	{
		fillTableError(vDateError);
	}
	else
	{
		for(size_t i =0;i < vDateError.size();i++)
		{			
			if (vDateError[i].errortype.error == errortype.toStdString())
			{
				vTemp.push_back(vDateError[i]);
			}		
		}
		fillTableError(vTemp);
	}
}
void dateerrortab::getcbYear(QString year)
{	
	if(year=="")
	{		
		fillTableError(vDateError);
	}
	else
	{
		std::vector<DateError> vTemp;
		for(size_t i =0;i < vDateError.size();i++)
		{			
			QDate date = date.fromString(vDateError[i].dateBegin.c_str(),"yyyy-MM-dd");
			if (date.year() == year.toInt())
			{
				vTemp.push_back(vDateError[i]);
			}		
		}
		fillTableError(vTemp);		
	}		
}

/*
void dateerrortab::getLine(int row,int col)
{	
	if ((col !=06) && (row!= 0))
	{
		std::string link;
		MetsError s = vSchemaE[row-1];
		link = batchDetail.path + s.mets.path + "/" + s.mets.fileName ;		
		ShellExecuteA(NULL, "open",link.c_str(), NULL, NULL, SW_SHOWNORMAL);
	}		
}
*/




void dateerrortab::fillTableError(std::vector<DateError> vError)
{			
	// vDateError = db.getDateError(batchDetail.idTestSet);	
	
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

	for (size_t i =0;i < vError.size();i++)
	{
		DateError dateError = vError[i];
		std::stringstream ss;
	
		ss << "Issue " << dateError.issues << " on ";
				
		QDate dateBegin = dateBegin.fromString(dateError.dateBegin.c_str(),"yyyy-MM-dd"); 
		QDate dateEnd = dateEnd.fromString(dateError.dateEnd.c_str(),"yyyy-MM-dd"); 	
		
	
		dateBegin = dateBegin.addDays(1);
		bool first =false;
		bool in = false;
	//	for (size_t j = dateBegin.toJulianDay();j < dateEnd.toJulianDay();j++)
		while ( dateBegin != dateEnd)
		{	
					
			if (dateBegin.dayOfWeek() ==7)
			{				
			//	j++;
			}
			else if (first ==false)
			{
				if (dateError.errortype.id == cat_duplicateIssue) //à changer par après
				{
					ss << dateEnd.toString("yyyy-MM-dd").toStdString();
					in = true;
					break;
					
				}
				else
				{
					ss << dateBegin.toString("yyyy-MM-dd").toStdString();					
				}				
				first = true;
				in = true;
			}
			else if (first == true)
			{
				ss << " to " << dateEnd.addDays(-1).toString("yyyy-MM-dd").toStdString();					
				in = true;
				break;
			}	
			dateBegin = dateBegin.addDays(1);			
		}
		
		if (in ==false)
		{
			ss << dateEnd.toString("yyyy-MM-dd").toStdString();
		}
		
		
	//	QString ss ;

		int col = 0;

		acceptedW* checkBox = new acceptedW(dateError.accepted,dateError.hashkey);
		table->setCellWidget(i+1, col++,checkBox);
		connect ( checkBox, SIGNAL(changeHash(bool,std::string)), this, SLOT(accepted(bool,std::string)));


		newItem = new QTableWidgetItem(dateError.errortype.severity.gravity.c_str(),i);		
		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(i+1, col++, newItem);
	
		newItem = new QTableWidgetItem(dateError.errortype.error.c_str(),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(i+1, col++, newItem);
		
		newItem = new QTableWidgetItem(ss.str().c_str(),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(i+1, col++, newItem);		
	}	
	table->resizeColumnsToContents();
	for (int i=0;i<table->columnCount();i++)
	{
		if (table->columnWidth(i) <100)
		{
			table->setColumnWidth(i,100);		
		}				
	}
	QGridLayout *grid = new QGridLayout();
	grid->addWidget(table, 0, 0);
	grid->setColumnStretch(0, 10);
	this->setLayout(grid);
}

void dateerrortab::fillCombo(int id_cat,const BatchDetail &batchDetail)
{
	std::vector<std::string> v = db.getDistinctErrorTypeDateError(id_cat,batchDetail.idTestSet);
	comboError->addItem("");	
	for (size_t i = 0;i < v.size();i++)
	{
		comboError->addItem(v[i].c_str());	
	}	
	
	std::map<int,std::pair<int,int>> m = db.getSumMetsYear(batchDetail.idTestSet);
	comboYear->addItem("");
	for (std::map<int,std::pair<int,int>>::iterator it = m.begin(); it!= m.end();it++)
	{
		QString ss;
		comboYear->addItem(ss.setNum(it->first));
	}	

	table->setCellWidget(0,2,comboError);
	table->setCellWidget(0,4,comboYear);

}
int dateerrortab::getSizeVError()
{
	return vDateError.size();
}

void dateerrortab::accepted(bool val,std::string hashkey){
	if ( val) {
		db.insertAccepted(hashkey);	
	}else{
		db.deleteAccepted(hashkey);
	}
}

