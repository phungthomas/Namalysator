#include "w_inventaire.h"
#include "ui_w_inventaire.h"
#include <QDate>
#include "gui_utilities.h"
#include <sstream>
#include "w_structview.h"
#include "calendarcommons.h"
#include "exportdata.h"


w_inventaire::w_inventaire(QWidget *parent)
    : QWidget(parent), ui(new Ui::w_inventaire)
{
    ui->setupUi(this);	
   	ui->table->setShowGrid(false);
	ui->table->verticalHeader()->hide();
	ui->table->setEditTriggers(false);
	ui->table->setAlternatingRowColors(true);		
	labelInventaire << tr("Jour") << tr("Mois")<< tr("Année")<< tr("Numéro")<< tr("Pages")<< tr("Supplément");
	labelInventaireTotal << tr("Jour") << tr("Mois")<< tr("Année")<< tr("Numéro")<< tr("Pages")<< tr("Supplément")<< tr("Suppl pages")<< tr("Type")<< tr("Jg") << tr("Annexes") << tr("Missing");
	changeNewDate = false;
	labels  << tr("Jour") << tr("Mois")<< tr("Année")<< tr("Numéro")<< tr("Pages")<< tr("Supplément")<<tr("Errors");
}
 
void w_inventaire::createConnections()
{
	connect(ui->table,SIGNAL(currentItemChanged(QTableWidgetItem *,QTableWidgetItem * )),this,SLOT(lineChanged(QTableWidgetItem *,QTableWidgetItem *)));
   	connect(ui->btnViewIssue,SIGNAL(clicked()),this,SLOT(viewIssue()));
   	connect(ui->btnInventaire,SIGNAL(clicked()),this,SLOT(showInventaire()));
   	connect(ui->btnExport,SIGNAL(clicked()),this,SLOT(exportIssues()));
   	connect(ui->btnShowErrors,SIGNAL(clicked()),this,SLOT(showErrors()));   	
   	connect(ui->comboYear,SIGNAL(currentIndexChanged(QString)),this, SLOT(getcbYear(QString)));	
}

void w_inventaire::viewIssue()
{	
	w_structview *view = new w_structview();	
    view->resize(1200,910);
    view->setBatchDetail(batch);
    view->setCurrentMets(currentMets);
    view->show();
}
void w_inventaire::showInventaire()
{
	 widgetInventaire->show();	
}

//! fill combobox of years
void w_inventaire::fillComboYear()
{
	std::map<int,std::pair<int,int>> m = db.getSumMetsYear(batch.idTestSet);
	ui->comboYear->addItem("");
	for (std::map<int,std::pair<int,int>>::iterator it = m.begin(); it!= m.end();it++)
	{
		QString ss;
		ui->comboYear->addItem(ss.setNum(it->first));
	}	
}

//! export issues to excel 
void w_inventaire::exportIssues()
{
	QString fileName = QFileDialog::getSaveFileName(this,tr("Open File"),"",tr("file (*.ods)"));    
     if (!fileName.isEmpty()) 
     {			
		 exportdata *data = new exportdata();
	//	 data->exportIssues(batch.mapMets,fileName.toStdString());
		 data->exportIssues(mapErrorMets,fileName.toStdString());		 
		 QMessageBox::information(this, tr("Namalysator"),
                                   tr("Export finished"));		
	}  	
}

void w_inventaire::showErrors()
{		
	fillMetsfromTestset(mapErrorMets);
	compareDate(mapErrorMets);	
}

void w_inventaire::getcbYear(QString cbyear)
{	
	std::map<int,MetsFile> temp;
	changeNewDate = false;	
	if(cbyear=="")
	{
		// TODO : Check out how this inventaire works
		// fillMetsfromTestset(batch.mapMets);
//		compareDate(batch.mapMets);
	}
	else
	{
		// TODO : Check out how this inventaire works
		/*
		for (std::map<int,MetsFile>::iterator it = batch.mapMets.begin(); it!= batch.mapMets.end();it++)	
		{
			if (it->second.date.year() == cbyear.toInt())
			{
				temp[it->first] = it->second;
			}
		}
		*/
		// TODO : Check out how this inventaire works
		// fillMetsfromTestset(temp);
		compareDate(temp);
	}
}

void w_inventaire::lineChanged(QTableWidgetItem * item1,QTableWidgetItem *item2)
{	/*
	item2 =0;
	if(ui->table->currentColumn() != 6 && item1 !=NULL)
	{		
		QString ss;	
		QTableWidgetItem * newItem;
		if (changeNewDate == true)
		{			
			ui->tableClickMissing->clearContents();
			ui->tableClickMissing->setColumnCount(labelInventaire.size());
			ui->tableClickMissing->setRowCount(1);	
			ui->tableClickMissing->setHorizontalHeaderLabels(labelInventaire);
			ui->tableClickMissing->verticalHeader()->hide();
			ui->tableClickMissing->resizeRowsToContents();	
		
			int	row = item1->row();
			// TODO : Check out how this inventaire works
			// std::map<int,MetsFile>::iterator itMets = batch.mapMets.find(item1->type());
			for (size_t i=0 ; i < vInventaire.size() ;i++)
			{	
				Excel *excel = &vInventaire[i];			
				QDate dateInventaire ;
				dateInventaire.setDate(excel->year,excel->month,excel->day);			
				// if(excel->issueNumber == itMets->second.vectIssueNumber && itMets->second.date.year() == excel->year)
				{	
					// currentMets	 = itMets->second;	
					widgetInventaire->selectRow(excel->id-1);			
					newItem = new QTableWidgetItem(ss.setNum(excel->day),currentMets.idMets);
					newItem->setTextAlignment(Qt::AlignCenter);
					ui->tableClickMissing->setItem(0,0,newItem);				
					newItem = new QTableWidgetItem(ss.setNum(excel->month),currentMets.idMets);
					newItem->setTextAlignment(Qt::AlignCenter);
					ui->tableClickMissing->setItem(0,1,newItem);
					newItem = new QTableWidgetItem(ss.setNum(excel->year),currentMets.idMets);
					newItem->setTextAlignment(Qt::AlignCenter);
					ui->tableClickMissing->setItem(0,2,newItem);
					newItem = new QTableWidgetItem(convertToStringIssueNumber(excel->issueNumber).c_str(),currentMets.idMets);
					newItem->setTextAlignment(Qt::AlignCenter);
					ui->tableClickMissing->setItem(0,3,newItem);
					newItem = new QTableWidgetItem(ss.setNum(excel->pages),currentMets.idMets);
					newItem->setTextAlignment(Qt::AlignCenter);
					ui->tableClickMissing->setItem(0,4,newItem);
					newItem = new QTableWidgetItem(excel->supplement.c_str(),currentMets.idMets);
					newItem->setTextAlignment(Qt::AlignCenter);
					ui->tableClickMissing->setItem(0,5,newItem);				
					break;		
				}
				// else if (itMets->second.date == dateInventaire )
				{ 
					// currentMets	 = itMets->second;	
					widgetInventaire->selectRow(excel->id-1);	
					newItem = new QTableWidgetItem(ss.setNum(excel->day),currentMets.idMets);
					newItem->setTextAlignment(Qt::AlignCenter);
					ui->tableClickMissing->setItem(0,0,newItem);				
					newItem = new QTableWidgetItem(ss.setNum(excel->month),currentMets.idMets);
					newItem->setTextAlignment(Qt::AlignCenter);
					ui->tableClickMissing->setItem(0,1,newItem);
					newItem = new QTableWidgetItem(ss.setNum(excel->year),currentMets.idMets);
					newItem->setTextAlignment(Qt::AlignCenter);
					ui->tableClickMissing->setItem(0,2,newItem);
					newItem = new QTableWidgetItem(convertToStringIssueNumber(excel->issueNumber).c_str(),currentMets.idMets);
					newItem->setTextAlignment(Qt::AlignCenter);
					ui->tableClickMissing->setItem(0,3,newItem);
					newItem = new QTableWidgetItem(ss.setNum(excel->pages),currentMets.idMets);
					newItem->setTextAlignment(Qt::AlignCenter);
					ui->tableClickMissing->setItem(0,4,newItem);
					newItem = new QTableWidgetItem(excel->supplement.c_str(),currentMets.idMets);
					newItem->setTextAlignment(Qt::AlignCenter);
					ui->tableClickMissing->setItem(0,5,newItem);				
					break;					  
				}	
			}	
			ui->table->selectRow(row);	
		}
		else
		changeNewDate = true;
	}*/
}

w_inventaire::~w_inventaire()
{
    delete ui;
}

void w_inventaire::fillMetsfromTestset(std::map<int,MetsFile> mapMets)
{	
	ui->table->clear();
	ui->table->setColumnCount(labels.size());
	ui->table->setRowCount(mapMets.size());
	QString ss;
	QTableWidgetItem *newItem ;
	
	ui->table->setHorizontalHeaderLabels(labels);
	int i=0;
	for (std::map<int,MetsFile>::iterator it = mapMets.begin(); it!= mapMets.end();it++)	
	{		
		MetsFile *mets = &it->second;		
		newItem = new QTableWidgetItem(ss.setNum(mets->date.day()),mets->idMets);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->table->setItem(i,0,newItem);				
		newItem = new QTableWidgetItem(ss.setNum(mets->date.month()),mets->idMets);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->table->setItem(i,1,newItem);
		newItem = new QTableWidgetItem(ss.setNum(mets->date.year()),mets->idMets);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->table->setItem(i,2,newItem);
		newItem = new QTableWidgetItem(convertToStringIssueNumber(mets->vectIssueNumber).c_str(),mets->idMets);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->table->setItem(i,3,newItem);
		newItem = new QTableWidgetItem(ss.setNum(mets->pages),mets->idMets);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->table->setItem(i,4,newItem);
		// TODO : Handle multiple supplements
		if (!mets->supplements.empty())
		{
			// KNOWNBUG only shows first item until we fix GUI
			newItem = new QTableWidgetItem(mets->supplements[0].c_str(), mets->idMets);
			newItem->setTextAlignment(Qt::AlignCenter);
			ui->table->setItem(i,5,newItem);
		}
		else
		{
			newItem = new QTableWidgetItem("No",mets->idMets);
			newItem->setTextAlignment(Qt::AlignCenter);
			ui->table->setItem(i,5,newItem);
		}
				
		i++;
	}
	ui->table->resizeRowsToContents();	
}

void w_inventaire::fillMetsfromInventory(QTableWidget *tableInventaire)
{
	QTableWidgetItem *newItem ;
	QString ss;
	tableInventaire->setColumnCount(labelInventaireTotal.size());
	tableInventaire->setRowCount(vInventaire.size());
	ui->table->setShowGrid(false);
	ui->table->verticalHeader()->hide();
	ui->table->setEditTriggers(false);
	ui->table->setAlternatingRowColors(true);		
	tableInventaire->setHorizontalHeaderLabels(labelInventaireTotal);
	for (size_t i=0 ; i < vInventaire.size() ;i++)
	{	
		Excel *excel = &vInventaire[i];	
		newItem = new QTableWidgetItem(ss.setNum(excel->day),excel->id);
		newItem->setTextAlignment(Qt::AlignCenter);
		tableInventaire->setItem(i,0,newItem);				
		newItem = new QTableWidgetItem(ss.setNum(excel->month),excel->id);
		newItem->setTextAlignment(Qt::AlignCenter);
		tableInventaire->setItem(i,1,newItem);
		newItem = new QTableWidgetItem(ss.setNum(excel->year),excel->id);
		newItem->setTextAlignment(Qt::AlignCenter);
		tableInventaire->setItem(i,2,newItem);
		newItem = new QTableWidgetItem(convertToStringIssueNumber(excel->issueNumber).c_str(),excel->id);
		newItem->setTextAlignment(Qt::AlignCenter);
		tableInventaire->setItem(i,3,newItem);
		newItem = new QTableWidgetItem(ss.setNum(excel->pages),excel->id);
		newItem->setTextAlignment(Qt::AlignCenter);
		tableInventaire->setItem(i,4,newItem);
		newItem = new QTableWidgetItem(QString::fromUtf8(excel->supplement.c_str()),excel->id);
		newItem->setTextAlignment(Qt::AlignCenter);
		tableInventaire->setItem(i,5,newItem);
		newItem = new QTableWidgetItem(ss.setNum(excel->supPages),excel->id);
		newItem->setTextAlignment(Qt::AlignCenter);
		tableInventaire->setItem(i,6,newItem);
		newItem = new QTableWidgetItem(excel->type.c_str(),excel->id);
		newItem->setTextAlignment(Qt::AlignCenter);
		tableInventaire->setItem(i,7,newItem);
		newItem = new QTableWidgetItem(ss.setNum(excel->jg),excel->id);
		newItem->setTextAlignment(Qt::AlignCenter);
		tableInventaire->setItem(i,8,newItem);

		
		if (excel->annexes ==0)
		newItem = new QTableWidgetItem("NO",excel->id);
		else
		newItem = new QTableWidgetItem("YES",excel->id);	
		
		newItem->setTextAlignment(Qt::AlignCenter);
		tableInventaire->setItem(i,9,newItem);
		
		if (excel->missing ==0)
		newItem = new QTableWidgetItem("NO",excel->id);
		else
		newItem = new QTableWidgetItem("YES",excel->id); 
		
		newItem->setTextAlignment(Qt::AlignCenter);
		tableInventaire->setItem(i,10,newItem);
										
	}
	tableInventaire->resizeRowsToContents();
}

	
void w_inventaire::setBatchDetail(const BatchDetail &d)
{ 	
	batch = d; 
	db.setDataBaseName(batch.database);  		
	fillComboYear();
	dbInventaire.setDataBaseName(batch.databaseInv);
	vInventaire = dbInventaire.getInventaire(batch.inventaire.id);
	mapInventaire = dbInventaire.getMapInventaire(batch.inventaire.id);	
    widgetInventaire = new  QTableWidget();
	fillMetsfromInventory(widgetInventaire);
	widgetInventaire->resize(1100,600);
	widgetInventaire->setShowGrid(false);
	widgetInventaire->verticalHeader()->hide();
	widgetInventaire->setEditTriggers(false);
	widgetInventaire->setAlternatingRowColors(true);	
//	fillMetsfromTestset(batch.mapMets);
	//fillMetsfromInventory(ui->tableInventaire);		
	createConnections();	
//	compareDate(batch.mapMets);	
}

void w_inventaire::compare()
{
	bool error;
	std::vector<Excel> vTempInventaire;
	std::vector<MetsFile*> vMetsMissing;
	vTempInventaire = vInventaire;	
	QTableWidgetItem *newItem ;
	QString ss;
	int i=0;
//	for (std::map<int,MetsFile>::iterator it = batch.mapMets.begin(); it!= batch.mapMets.end();it++)
	{	
		std::stringstream s;
		s<<"";
		MetsFile *mets; // = &it->second;		
		QDate dateInventaire ;
		for (size_t j=0 ; j < vTempInventaire.size() ;j++)
		{	
			Excel *excel = &vTempInventaire[j];				
			dateInventaire.setDate(excel->year,excel->month,excel->day);			
			if (mets->vectIssueNumber == excel->issueNumber && mets->date.year() == excel->year)
			{
				 error = false;
				//verification number of pages
				if (excel->pages != mets->pages )
				{
					s << " error pages" ;								
					ui->table->item(i,4)->setTextColor("red");					 
					error = true;					
				}
				// TODO : fix Excel inventaire to also have several supplements and then correctly compare with METS
				/*
				if (excel->supplement != mets->supplement)
				{
					s << " error supplément" ;
					ui->table->item(i,5)->setTextColor("red"); 
					error = true;					
				} */
				if (mets->date != dateInventaire)
				{
					s<< " wrong date";	
					ui->table->item(i,0)->setTextColor("red"); 	
					ui->table->item(i,1)->setTextColor("red"); 
					ui->table->item(i,2)->setTextColor("red"); 		
					error = true;					
				}		
				vTempInventaire.erase(vTempInventaire.begin()+ j); 							
				break;	
			}
			else if (mets->date == dateInventaire)
			{
				s<< "Wrong issue number???";	
				ui->table->item(i,3)->setTextColor("red"); 
				error = true;			
				break;
			}	
		}
		if (error ==false)
		{
			vMetsMissing.push_back(mets);
		}
			//newItem = new QTableWidgetItem(s.str().c_str(),it->first);				
			if (error ==true)
			{		        
			}			
			ui->table->setItem(i,6,newItem);		
			i++;
	}
	
	ui->table->resizeRowsToContents();
	ui->table->resizeColumnsToContents();
	
	for (size_t i =0;i < ui->table->columnCount();i++)
	{
		if( ui->table->columnWidth(i) < 100)
			ui->table->setColumnWidth(i,100);	
	}	
	
	ui->tableMissingInventaire->setColumnCount(labelInventaire.size());
	ui->tableMissingInventaire->setRowCount(vTempInventaire.size());	
	ui->tableMissingInventaire->setHorizontalHeaderLabels(labelInventaire);
	for (size_t i=0 ; i < vTempInventaire.size() ;i++)
	{	
		Excel *excel = &vTempInventaire[i];		
		newItem = new QTableWidgetItem(ss.setNum(excel->id),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableMissingInventaire->setItem(i,0,newItem);
		newItem = new QTableWidgetItem(ss.setNum(excel->day),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableMissingInventaire->setItem(i,1,newItem);				
		newItem = new QTableWidgetItem(ss.setNum(excel->month),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableMissingInventaire->setItem(i,2,newItem);
		newItem = new QTableWidgetItem(ss.setNum(excel->year),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableMissingInventaire->setItem(i,3,newItem);
		newItem = new QTableWidgetItem(convertToStringIssueNumber(excel->issueNumber).c_str(),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableMissingInventaire->setItem(i,4,newItem);
		newItem = new QTableWidgetItem(ss.setNum(excel->pages),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableMissingInventaire->setItem(i,5,newItem);
		newItem = new QTableWidgetItem(QString::fromUtf8(excel->supplement.c_str()),i);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableMissingInventaire->setItem(i,6,newItem);			
	}
	ui->tableMissingInventaire->resizeRowsToContents();		
	ui->tableEnTrop->setColumnCount(labels.size());
	ui->tableEnTrop->setRowCount(vMetsMissing.size());
	ui->tableEnTrop->setHorizontalHeaderLabels(labels);
	
	for (size_t i=0 ; i < vMetsMissing.size() ;i++)
	{	
		MetsFile *mets = vMetsMissing[i];		
		
		newItem = new QTableWidgetItem(ss.setNum(mets->date.day()),mets->idMets);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableEnTrop->setItem(i,0,newItem);				
		newItem = new QTableWidgetItem(ss.setNum(mets->date.month()),mets->idMets);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableEnTrop->setItem(i,1,newItem);		
		newItem = new QTableWidgetItem(ss.setNum(mets->date.year()),mets->idMets);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableEnTrop->setItem(i,2,newItem);
		newItem = new QTableWidgetItem(convertToStringIssueNumber(mets->vectIssueNumber).c_str(),mets->idMets);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableEnTrop->setItem(i,3,newItem);
		newItem = new QTableWidgetItem(ss.setNum(mets->pages),mets->idMets);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableEnTrop->setItem(i,4,newItem);
		if (!mets->supplements.empty()) {
			// TODO : handle multiple supplements
			// KNOWNBUG 
			newItem = new QTableWidgetItem(QString::fromUtf8(mets->supplements[0].c_str()),mets->idMets);
		}
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableEnTrop->setItem(i,5,newItem);		
	}
	ui->tableEnTrop->resizeRowsToContents();
		
	for (size_t i=0; i< vTempInventaire.size();i++)
	{
		Excel *excel = &vTempInventaire[i];	
		QDate dateInventaire ;
		dateInventaire.setDate(excel->year,excel->month,excel->day);
		for (size_t j=0;j< vMetsMissing.size();j++)
		{		
			MetsFile *mets = vMetsMissing[j];				
			if (mets->date == dateInventaire)
			{
				if (excel->issueNumber != mets->vectIssueNumber)
				{					
					vMetsMissing.erase(vMetsMissing.begin() + j);					
					newItem = new QTableWidgetItem("wrong issue number?",mets->idMets);					
					ui->tableEnTrop->setItem(i,6,newItem);						
				}
			}					
		}	
	}	
}

bool w_inventaire::compareIssueNumber(MetsFile *mets,int currentLine)
{
	std::vector<Excel> vTempInventaire;	
	vTempInventaire = vInventaire;	
	bool notFound = false;
	for (size_t i=0; i< vTempInventaire.size();i++)
	{
		Excel *excel = &vTempInventaire[i];	
		QDate dateInventaire ;
		dateInventaire.setDate(excel->year,excel->month,excel->day);
		
		if (mets->vectIssueNumber == excel->issueNumber && mets->date.year() == excel->year)
		{			
			if (mets->date != dateInventaire)
			{
			//	s<< " wrong date";	
				ui->table->item(currentLine,0)->setTextColor("red"); 	
				ui->table->item(currentLine,1)->setTextColor("red"); 
				ui->table->item(currentLine,2)->setTextColor("red"); 	
				vErrorMets.push_back(*mets);	
				mapErrorMets[mets->idMets]= *mets;			
				notFound =true;	
				return true;		
			}		
		}	
	}	
	vNotReferencedMets.push_back(*mets);		
	return false;
}

void w_inventaire::compareDate(std::map<int,MetsFile> mapMets)
{	
	bool isError = false;
	bool isErrorIssue = false;
	bool isErrorPages = false;
	bool isErrorSupplement = false;		
	
	vErrorMets.clear();
	mapErrorMets.clear();
	vNotReferencedMets.clear();
	int i=0;
	for (std::map<int,MetsFile>::iterator itMets = mapMets.begin(); itMets!= mapMets.end();itMets++)	
	{	
		MetsFile *mets = &itMets->second;
		
		if (mapInventaire.find(mets->date) != mapInventaire.end())
		{			
			//date trouvée
			isErrorIssue = false;
			isErrorPages = false;
			isErrorSupplement = false;
			isError = false;
			std::map<QDate,std::vector<Excel> >::iterator it = mapInventaire.find(mets->date) ;
			for(size_t j=0;j< it->second.size();j++)
			{
				isErrorIssue = false;
				isErrorPages = false;
				isErrorSupplement = false;
				
				Excel *excel = &it->second[j];
				isError = false;
				if (mets->vectIssueNumber != excel->issueNumber)
				{					
					isErrorIssue = true;
					isError = true;								
				}
				else
				{
					isErrorIssue = false;				
				}
				
				if (mets->pages != excel->pages)
				{
					isErrorPages = true;
					isError = true;					
				}
				else
				{
					isErrorPages = false;
				}
				
				// TODO : fix inventaire for more supplements
				/*
				if (mets->supplement != excel->supplement)
				{
					isErrorSupplement = true;		
					isError = true;				
				}
				else
				{
					isErrorSupplement = false;
				}			*/	
				
				if (isError==false)
				{				
					isErrorPages = false;
					isErrorPages = false;
					isErrorSupplement = false;			
					break;
				}									
			}								
		}		
		else
		{
		//	vNotReferencedMets.push_back(itMets->second);	
			if (compareIssueNumber(&itMets->second,i)==false)
			{
				ui->table->item(i,0)->setTextColor("green");
				ui->table->item(i,1)->setTextColor("green"); 
				ui->table->item(i,2)->setTextColor("green"); 
				ui->table->item(i,3)->setTextColor("green"); 
				ui->table->item(i,4)->setTextColor("green"); 
				ui->table->item(i,5)->setTextColor("green");				 			
			};				
		}
		
		if (isError == true)
		{	
			std::stringstream s;
			s<<"";
			
			if (isErrorIssue ==true)
			{
				ui->table->item(i,3)->setTextColor("red"); 
				s << " error issueNumber" ;	
				isErrorIssue = false;
			}
			if (isErrorPages ==true)
			{
				ui->table->item(i,4)->setTextColor("red"); 	
				s << " error pages" ;	
				isErrorPages = false;
			}
			if (isErrorSupplement ==true)
			{
				ui->table->item(i,5)->setTextColor("red"); 	
				s << " error supplément" ;	
				isErrorSupplement = false;
			}			
			QTableWidgetItem *newItem = new QTableWidgetItem(s.str().c_str(),itMets->first);							
			ui->table->setItem(i,6,newItem);			
			
			vErrorMets.push_back(itMets->second);	
			mapErrorMets[itMets->first]= itMets->second;			
		}			
		i++;
	}
	fillNotReferencedissues();
}

void w_inventaire::fillNotReferencedissues()
{
	QTableWidgetItem *newItem;
	QString ss;
	ui->tableEnTrop->setColumnCount(labelInventaire.size());
	ui->tableEnTrop->setHorizontalHeaderLabels(labelInventaire);
	ui->tableEnTrop->verticalHeader()->hide();
	ui->tableEnTrop->setRowCount(vNotReferencedMets.size());	
	for (size_t i=0; i< vNotReferencedMets.size();i++)
	{		
		MetsFile *mets = &vNotReferencedMets[i];
		newItem = new QTableWidgetItem(ss.setNum(mets->date.day()),mets->idMets);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableEnTrop->setItem(i,0,newItem);				
		newItem = new QTableWidgetItem(ss.setNum(mets->date.month()),mets->idMets);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableEnTrop->setItem(i,1,newItem);		
		newItem = new QTableWidgetItem(ss.setNum(mets->date.year()),mets->idMets);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableEnTrop->setItem(i,2,newItem);
		newItem = new QTableWidgetItem(convertToStringIssueNumber(mets->vectIssueNumber).c_str(),mets->idMets);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableEnTrop->setItem(i,3,newItem);
		newItem = new QTableWidgetItem(ss.setNum(mets->pages),mets->idMets);
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableEnTrop->setItem(i,4,newItem);
		// TODO: fix for more supplements
		if (!mets->supplements.empty()) {
			newItem = new QTableWidgetItem(QString::fromUtf8(mets->supplements[0].c_str()),mets->idMets);
		}
		newItem->setTextAlignment(Qt::AlignCenter);
		ui->tableEnTrop->setItem(i,5,newItem);		
	}
}

