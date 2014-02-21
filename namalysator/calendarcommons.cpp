#include "calendarcommons.h"
#include <QTableWidget>
#include <QStringList>

void  initCalendarWidget(QCalendarWidget * calendarWidget, const BatchDetail &batch)
{	
	QDate minDate = minDate.fromString(batch.minDate.c_str(),"yyyy-MM-dd");
	minDate.setDate(minDate.year(),1,1);
	QDate maxDate = maxDate.fromString(batch.maxDate.c_str(),"yyyy-MM-dd");
	maxDate.setDate(maxDate.year(),12,31);
	calendarWidget->setMinimumDate(minDate);	 
	calendarWidget->setMaximumDate(maxDate);
	calendarWidget->setCurrentPage (minDate.year(),1);
	
	formatCalendar(calendarWidget);
	dbrequest db;
	db.setDataBaseName(batch.database);
	// TODO : Figure out if this calendarWidget needs all dates and how many times we call this function.
	std::vector<QDate> in_period = db.getMetsDates(batch.idTestSet);
	QTextCharFormat formatdate;
	formatdate.setBackground(QBrush("yellow", Qt::SolidPattern));
	for (std::vector<QDate>::const_iterator it = in_period.begin(); it!= in_period.end();it++)
	{
		calendarWidget->setDateTextFormat(*it, formatdate);
		
	}
}

void loadYear(QTableWidget *table,const BatchDetail &batch)
{
	int count=0;	
	table->setColumnCount(3);
	dbrequest db;
	db.setDataBaseName(batch.database);
	std::map<int ,std::pair<int, int> > mapYearCount = db.GetYearSummary(batch.idTestSet);
	table->setRowCount(mapYearCount.size());
	table->setColumnWidth(0,79);
	table->setColumnWidth(1,79);
	table->setColumnWidth(2,79);
	QStringList labelMets;
	labelMets  << "Year" << "Issues" << "Supplement";
	table->setHorizontalHeaderLabels(labelMets);	
	table->setShowGrid(false);
	table->verticalHeader()->hide();
	table->setEditTriggers(false);
	table->setAlternatingRowColors(true);
	
	QTableWidgetItem *newItem;	
	QString ss;
	for(std::map<int,std::pair<int,int>>::const_iterator it = mapYearCount.begin(); it != mapYearCount.end(); it++)
	{
		newItem = new QTableWidgetItem(ss.setNum(it->first),0);
		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(count, 0, newItem);
		newItem = new QTableWidgetItem(ss.setNum(it->second.first),1);
		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(count, 1, newItem);
		newItem = new QTableWidgetItem(ss.setNum(it->second.second),2);
		newItem->setTextAlignment(Qt::AlignCenter);
		table->setItem(count, 2, newItem);	
		table->setRowHeight(count,15);
		count++;		
	}	
}

void formatCalendar(QCalendarWidget *cal)
{
	QTextCharFormat formatdate;
    formatdate.setForeground(QBrush("black", Qt::SolidPattern));
	cal->setWeekdayTextFormat(Qt::Saturday,formatdate);
	cal->setWeekdayTextFormat(Qt::Sunday,formatdate);	

} 