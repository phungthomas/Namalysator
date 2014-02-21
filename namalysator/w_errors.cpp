#include "w_errors.h"
#include "ui_w_errors.h"
#include "qwidgettaberror.h"
#include "w_summaryerrors.h"
#include "dateerrortab.h"
#include <QFileDialog>
#include "exportdata.h"

w_errors::w_errors(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::w_errors)
{
    m_ui->setupUi(this);  
   
    connect(m_ui->btnExport, SIGNAL(clicked()),this, SLOT(exportExcel()));	
}

w_errors::~w_errors()
{
    delete m_ui;
}

void w_errors::changeEvent(QEvent *e)
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
//! set detail of the batch
void w_errors::setBatchDetail(const BatchDetail &d)
{ 	
	batchdetail = d; 
	getTaberrors();
}

void w_errors::getTaberrors()
{
	w_summaryerrors *w_s = new w_summaryerrors();
	dbrequest db;
	db.setDataBaseName(batchdetail.database);
	w_s->setBatchDetail(batchdetail);
	m_ui->scrollAreaErrorTable->setWidget(w_s);	
	std::vector<ErrorCategory> vCategory = db.getErrorCategory(); 	
	for (size_t i=0; i< vCategory.size();i++)
	{
		tabErrors *e = new tabErrors(vCategory[i].id_category,batchdetail);	
		if (e->getSizeVError() !=0)
		{			
			m_ui->tabWidget->insertTab(i+1,e,vCategory[i].name.c_str());		
		}
	}
	dateerrortab *d = new dateerrortab(6,batchdetail);		
	if( d->getSizeVError() !=0)
		m_ui->tabWidget->addTab(d,"DATES");	
}
void w_errors::exportExcel()
{
	QString fileName = QFileDialog::getSaveFileName(this,tr("Open File"),"",tr("file (*.ods)"));
    
     if (!fileName.isEmpty()) 
     {			
		 exportdata *data = new exportdata();
		 data->exportErrors(batchdetail,fileName.toStdString());
	}  	
}