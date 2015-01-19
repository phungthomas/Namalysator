#include "w_summaryerrors.h"
#include "ui_w_summaryerrors.h"
#include "qwidgettaberror.h"
#include "calendarcommons.h"
w_summaryerrors::w_summaryerrors(QWidget *parent) :
QWidget(parent),
m_ui(new Ui::w_summaryerrors)
{
	m_ui->setupUi(this);   
}

w_summaryerrors::~w_summaryerrors()
{
	delete m_ui;
}

void w_summaryerrors::changeEvent(QEvent *e)
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

//set detail of the batch
void w_summaryerrors::setBatchDetail()
{ 	
	db.setDataBaseName(BatchDetail::getBatchDetail().database);	
	loadTableSummary();
	loadYear(m_ui->tableYear,BatchDetail::getBatchDetail());
	loadTextbox();
}

/// <summary>load table with summary of the errors </summary>
void w_summaryerrors::loadTableSummary()
{
	std::vector<ErrorSummary> vEs = db.getvErrorSummary(BatchDetail::getBatchDetail().idTestSet);	
	m_ui->tableSummary->setColumnCount(6);
	m_ui->tableSummary->setRowCount(vEs.size());
	labels  << tr("Severity") << tr("Error Category") << tr("Count")<< tr("Nb. of issues affected")<< tr("Percentage") << tr("Details on sheet");// << tr("Number of issues");
	m_ui->tableSummary->setHorizontalHeaderLabels(labels);	
	m_ui->tableSummary->setShowGrid(true);
	m_ui->tableSummary->verticalHeader()->hide();
	m_ui->tableSummary->setRowHeight(0,20);

	for (int i=0;i<m_ui->tableSummary->rowCount();i++)
	{
		m_ui->tableSummary->setRowHeight(i,20);
	}

	for (int i=0;i<m_ui->tableSummary->columnCount();i++)
	{
		m_ui->tableSummary->setColumnWidth(i,100);
	}

	QString ss;	 
	QTableWidgetItem *newItem;
	for(size_t i=0;i < vEs.size();i++)
	{
		int countErrorMets = db.getcountMetsErrorForEachErrorType(BatchDetail::getBatchDetail().idTestSet,vEs[i].errorType.id);
		newItem = new QTableWidgetItem(vEs[i].errorType.severity.gravity.c_str(),0);		
		newItem->setTextAlignment(Qt::AlignCenter);
		m_ui->tableSummary->setItem(i, 0, newItem);
		newItem = new QTableWidgetItem(vEs[i].errorType.error.c_str(),1);		
		newItem->setTextAlignment(Qt::AlignCenter);
		m_ui->tableSummary->setItem(i, 1, newItem);
		newItem = new QTableWidgetItem(ss.setNum(vEs[i].count),2);		
		newItem->setTextAlignment(Qt::AlignCenter);
		m_ui->tableSummary->setItem(i, 2, newItem);		 
		newItem = new QTableWidgetItem(ss.setNum(countErrorMets),3);	
		newItem->setTextAlignment(Qt::AlignCenter);	
		m_ui->tableSummary->setItem(i, 3, newItem);		

		float percentage = float(countErrorMets) / float(BatchDetail::getBatchDetail().count) *100 ;
		char tmp[20];
		sprintf_s(tmp, "%.2f", percentage);			
		newItem = new QTableWidgetItem(tmp,4);	
		newItem->setTextAlignment(Qt::AlignCenter);	
		m_ui->tableSummary->setItem(i, 4, newItem);
		newItem = new QTableWidgetItem(vEs[i].errorType.category.name.c_str(),5);		
		newItem->setTextAlignment(Qt::AlignCenter);
		m_ui->tableSummary->setItem(i, 5, newItem);
	}
}

void w_summaryerrors::loadTextbox()
{
	QString ss;
	m_ui->lbSummary->setText(BatchDetail::getBatchDetail().batchName.c_str());	
	m_ui->lbDate->setText(BatchDetail::getBatchDetail().testDate.c_str());
	m_ui->lbTotal->setText(ss.setNum(BatchDetail::getBatchDetail().count));
	m_ui->lbTotal2->setText(ss.setNum(BatchDetail::getBatchDetail().count));
	m_ui->lbTitles->setText(ss.setNum(db.getcountTitleCheck(BatchDetail::getBatchDetail().idTestSet)));	
	int error = db.getcountMetsError(BatchDetail::getBatchDetail().idTestSet);
	int correct = BatchDetail::getBatchDetail().count - error;
	m_ui->lbCorrectIssues->setText(ss.setNum(correct));	
	float percent = float(correct) / float(BatchDetail::getBatchDetail().count) * 100;
	char tmp[20];
	sprintf_s(tmp, "%.2f", percent);
	m_ui->lbPercent->setText(tmp);	
}