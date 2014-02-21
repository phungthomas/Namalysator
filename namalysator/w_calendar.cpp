#include "w_calendar.h"
#include "ui_w_calendar.h"
#include <QMessageBox>
#include <sstream>
#include <map>
#include <QByteArray>
#include <QBuffer>
#include <windows.h>
#include <stdio.h>

w_calendar::w_calendar(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::w_calendar)
{
    m_ui->setupUi(this);
    m_ui->scrollAreaHeader->setWidget(m_ui->lblHeader); 
    m_ui->btnViewMets->setEnabled(false);
    createConnections();
}

//! create signals - slots
void w_calendar::createConnections()
{
	connect(m_ui->listMets,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(clickIdMets(QListWidgetItem*)));
    connect(m_ui->cbYear, SIGNAL(currentIndexChanged(QString)),this, SLOT(clickYear(QString)));
	connect(m_ui->btnViewMets,SIGNAL(clicked()),this,SLOT(viewMets()));  	
    for (int i=1;i<13;i++)
    {   
		connect(getCalendarFromMonth(i),SIGNAL(clicked(QDate)),this,SLOT(clickDate(QDate)));
		connect(getCalendarFromMonth(i),SIGNAL(activated(QDate)),this,SLOT(addComment(QDate)));      
    } 
    connect(m_ui->btnAddComment,SIGNAL(clicked()),this,SLOT(validerComment()));
    connect(m_ui->btnCancel,SIGNAL(clicked()),this,SLOT(cancel()));
}

w_calendar::~w_calendar()
{
    delete m_ui;
}

void w_calendar::fillcomboBoxYear()
{	
	std::map<int,std::pair<int,int>>mapYear  = db.getSumMetsYear(batchdetail.idTestSet);
	for(std::map<int,std::pair<int,int>>::iterator it = mapYear.begin(); it != mapYear.end(); it++)
	{
		QString s;		
		m_ui->cbYear->addItem(s.setNum(it->first));
	}
}

void w_calendar::setMapComment()
{
	mapComment = db.getDateComment(batchdetail.idTestSet);
} 

void w_calendar::setBatchDetail(const BatchDetail &d)
{ 
	batchdetail = d; 	
	db.setDataBaseName(batchdetail.database);  	
	fillcomboBoxYear();
	setMapComment();
	setRemarks();
}

void w_calendar::changeEvent(QEvent *e)
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

void w_calendar::fillcalendar(int month,int year,QCalendarWidget *calendar)
{	
	std::vector<QDate> v = db.getMetsDateInMonth(batchdetail.idTestSet, year, month);
	calendar->setEnabled(true);
	for(size_t j=0;j< v.size();j++)
	{
		setColor(v[j], "yellow", calendar);
	}
	QDate dateMin;
	dateMin.setDate(year,month,1);
	calendar->setMinimumDate(dateMin);
	calendar->setCurrentPage(year,month);
	QDate dateMax;
	dateMax.setDate(year,month,getLastDayOfMonth(month,year));
	calendar->setMaximumDate(dateMax);
}

void w_calendar::viewMets()
{
	std::string link;		
	link = batchdetail.path + mets.path; // Open directory  + "/" + mets.fileName ;		
	ShellExecuteA(NULL, "open",link.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void w_calendar::showMissingIssue()
{
	return;
	vDateError = db.getvDateError(batchdetail.idTestSet);
	
	for(size_t i=0;i< vDateError.size();i++)
	{	
		QDate dateEnd = dateEnd.fromString(vDateError[i].second.dateEnd.c_str(),"yyyy-MM-dd");
		if (vDateError[i].second.errorType == cat_duplicateIssue)
		{	
			setColor(dateEnd,"red",getCalendarFromMonth(dateEnd.month()));								
		}
		else
		{	
	
			QDate dateBegin = dateBegin.fromString(vDateError[i].second.dateBegin.c_str(),"yyyy-MM-dd");
			QDate dateEnd = dateEnd.fromString(vDateError[i].second.dateEnd.c_str(),"yyyy-MM-dd");
			bool find = false;
			dateBegin = dateBegin.addDays(1);
			while ( dateBegin < dateEnd && dateBegin.year() == m_ui->cbYear->currentText().toInt())
			{
				if (dateBegin.dayOfWeek() != 7)
				{
					setColor(dateBegin,"green",getCalendarFromMonth(dateBegin.month()));
					find = true;						
				}
				dateBegin = dateBegin.addDays(1);
			}
			if (find ==false)
			{
				setColorError(dateEnd,"yellow",getCalendarFromMonth(dateBegin.month()));
			
			}
		}
	}
	m_ui->listWidget->clear();
	for(size_t i=0;i< vDateError.size();i++) 
	{		
		QDate date = date.fromString(vDateError[i].second.dateEnd.c_str(),"yyyy-MM-dd");
		if (date.year() == m_ui->cbYear->currentText().toInt()) 
		{
			 lst =new QListWidgetItem(vDateError[i].second.comment.c_str(),  m_ui->listWidget,vDateError[i].second.id);
		}
	}
	
	
}

int w_calendar::getLastDayOfMonth(int month,int year)
{
	if ((month ==1) ||(month ==3) ||(month ==5) ||(month ==7) ||(month ==8) ||(month ==10) ||(month ==12))
			return 31;		
	if((month ==4) ||(month ==6) ||(month ==9) ||(month ==11))
		return 30;
		
	if ((year % 4) ==0)
		if ((year % 100) ==0)
			if ((year % 400) ==0)
				return 29;
			else
				return 28;
		else
			return 29;
	else
		return 28;	
}


void w_calendar::setCalendar(int year)
{
	QDate minDate;
	QDate maxDate;

	minDate = minDate.fromString(batchdetail.minDate.c_str(), "yyyy-MM-dd");
	
	for (int i=1;i< 13;i++)
	{
		QTextCharFormat formatdate;
		formatdate.setForeground(QBrush("black", Qt::SolidPattern));
		getCalendarFromMonth(i)->setWeekdayTextFormat(Qt::Saturday,formatdate);
		getCalendarFromMonth(i)->setWeekdayTextFormat(Qt::Sunday,formatdate);
		fillcalendar(i, year,getCalendarFromMonth(i));
	}
}

void w_calendar::setColor(QDate date,QColor color,QCalendarWidget *calendar)
{
	
    QTextCharFormat formatdate;
    formatdate.setBackground(QBrush(color, Qt::SolidPattern));        
    calendar->setDateTextFormat(date, formatdate);
    
}

void w_calendar::setColorError(QDate date,QColor color,QCalendarWidget *calendar)
{	
    QTextCharFormat formatdate;
    formatdate.setFontUnderline(true);
    formatdate.setUnderlineColor("green");
    formatdate.setBackground(QBrush(color, Qt::SolidPattern));        
    calendar->setDateTextFormat(date, formatdate);    
}


QCalendarWidget *w_calendar::getCalendarFromMonth(int i)
{
	if (i==1)   return m_ui->calendarJan;
	if (i==2)	return m_ui->calendarFev;
	if (i==3)	return m_ui->calendarMar;
	if (i==4)	return m_ui->calendarApr;
	if (i==5)	return m_ui->calendarMai;
	if (i==6)	return m_ui->calendarJun;
	if (i==7)	return m_ui->calendarJul;
	if (i==8)	return m_ui->calendarAug;
	if (i==9)	return m_ui->calendarSep;
	if (i==10)	return m_ui->calendarOct;
	if (i==11)	return m_ui->calendarNov;
	if (i==12)	return m_ui->calendarDec;

return  m_ui->calendarJan;
}
void w_calendar::displayHeader()
{
	std::map<int,LinkedFiles> tifPath = db.getMapLinkedFiles(mets.idMets,"IMGGRP");	
	std::string path = batchdetail.path  + mets.path + "" + tifPath[1].fileName;
	
	QImage image(path.c_str());

	if (image.isNull()) 
	{
		QMessageBox::information(this, tr("Image Viewer"),
                                      tr("Cannot load %1.").arg(path.c_str()));
	}
	
	image = image.copy(0,0,image.width(),1000);
	image = image.scaled(900,300);	
	
	m_ui->lblHeader->setPixmap(QPixmap::fromImage(image));
	m_ui->scrollAreaHeader->setWidgetResizable(true);
	
} 
//TODO comment datechanged
void w_calendar::clickDate(QDate search)
{
	m_ui->btnViewMets->setEnabled(true);
	clearGroupBox();
	clearDetails();
	QDate date;
	std::stringstream sPath;	
	m_ui->listMets->clear();
	listOfMetsOnDay.clear();

	m_ui->dateComment->setText(search.toString("yyyy-MM-dd"));

	bool findfirst = false;

	std::vector<MetsFile> result;
	if (batchdetail.getMetsByDate(search, result)) {
		for (std::vector<MetsFile>::const_iterator it = result.begin(); it != result.end(); it++) {
			listOfMetsOnDay[it->idMets] = *it;
			lst = new QListWidgetItem(it->fileName.c_str(), m_ui->listMets, it->idMets);	
			if (findfirst == false) {
				mets = *it;
				displayHeader();
				displayDetails();
				findfirst = true;
			}
		}
	} else {
		// some weird error
		QMessageBox::information(this, tr("Error"), search.toString("yyyy-MM-dd") + tr(" has supposedly a METS that I don't know about"));
	}
}

void w_calendar::displayDetails()
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
	std::map<int,LinkedFiles> mapAltoPath = db.getMapLinkedFiles(mets.idMets,"ALTOGRP");	
	int temp = mapAltoPath.size();
	m_ui->lbPages->setNum(temp);	
	m_ui->listSupplement->clear();
	
	if (!mets.supplements.empty()) {
		for (std::vector<std::string>::const_iterator it = mets.supplements.begin(); it != mets.supplements.end(); ++it) {
			new QListWidgetItem(QString::fromUtf8(it->c_str()), m_ui->listSupplement, 0);
		}
	}
}

void w_calendar::clickIdMets(QListWidgetItem* item )
{
	std::stringstream sPath;
	
	std::map<int,MetsFile>::iterator iter = listOfMetsOnDay.find(item->type());	
	if (iter != listOfMetsOnDay.end()) {
		mets = iter->second;
		displayHeader();
		displayDetails();
	} else {
		QMessageBox::information(this, tr("listOfMetsOnDay"), tr("The Map of METS files is empty"));
	}
}

void w_calendar::clickYear(QString cbYear)
{	
	int year;
	year = cbYear.toInt();
	setCalendar(year);
	setRemarks();
	showMissingIssue();

}

void w_calendar::addComment(QDate date)
{	
clearGroupBox();
//	 m_ui->groupBoxComment->setEnabled(true);
	  m_ui->dateComment->setText(date.toString("yyyy-MM-dd"));	
}

void w_calendar::validerComment()
{	
	
	QDate date;
	date = date.fromString(m_ui->dateComment->text(),"yyyy-MM-dd");	
	std::map<QDate,DateComment>::iterator it2 = mapComment.find(date);
	{		
		if (it2 != mapComment.end())
		{
			db.updateDateComment(it2->second.id,m_ui->txtComment->toPlainText().toStdString());
		}
		else
		{
		
			for(size_t i=0;i< vDateError.size();i++)
			{
				QDate dateBegin = dateBegin.fromString(vDateError[i].second.dateBegin.c_str(),"yyyy-MM-dd");
				QDate dateEnd = dateEnd.fromString(vDateError[i].second.dateEnd.c_str(),"yyyy-MM-dd");
		
				if (vDateError[i].second.errorType == cat_duplicateIssue)
				{
					if (dateEnd == date)
					{
						int id = vDateError[i].first;
						db.insertComment(id,m_ui->dateComment->text().toStdString(),m_ui->txtComment->toPlainText().toStdString());
						break;
					}
				}
				else if (dateBegin < date && dateEnd > date)
				{
					int id = vDateError[i].first;
					db.insertComment(id,m_ui->dateComment->text().toStdString(),m_ui->txtComment->toPlainText().toStdString());
					break;
				}
			}
		}			
	}
	
	date = date.fromString(m_ui->dateComment->text(),"yyyy-MM-dd");		
	setColor(date,"blue",getCalendarFromMonth(date.month()));	
	setMapComment();
}

void w_calendar::setRemarks()
{	
	for (std::map<QDate,DateComment>::iterator it = mapComment.begin(); it!= mapComment.end();it++)	
	{	
		setColor(it->first,"blue",getCalendarFromMonth(it->second.date.month()));
	}	
}

void w_calendar::clearGroupBox()
{		
	m_ui->dateComment->clear();
	m_ui->txtComment->clear();
//	m_ui->groupBoxComment->setEnabled(false);	

}

void w_calendar::cancel()
{
	clearGroupBox();
}

void w_calendar::clearDetails()
{
	m_ui->lbFileName->setText("");
	m_ui->lbIssueNumber->setText("");
	m_ui->lbIssueParsed->setText("");
	m_ui->lbPages->setText("");
	m_ui->listSupplement->clear();
	m_ui->lblHeader->clear();
	m_ui->listMets->clear();
	m_ui->scrollAreaHeader->setWidget(m_ui->lblHeader);
}


