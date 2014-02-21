#include "w_main.h"
#include "ui_w_main.h"
#include "odswriter.h"
#include "w_disk.h"
#include "w_calendar.h"
#include "w_structview.h"
#include "w_titlecheck.h"
#include "w_errors.h"
#include "w_exportdata.h"
#include "qwidgettaberror.h"
#include "w_selectbatch.h"
#include "w_errors.h"
#include "exportdata.h"
#include "w_inventaire.h"

w_main::w_main(QWidget *parent) :
QMainWindow(parent),
m_ui(new Ui::w_main)
{
	m_ui->setupUi(this);    
	   

}

void w_main::setBatchDetail(const BatchDetail &d)
{ 
	batch = d;
	parseBatch();
	createActions();  
}

w_main::~w_main()
{
	delete m_ui;
}

void w_main::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		m_ui->retranslateUi(this);
		break;
	default:
		break;
	}
}

void w_main::createActions()
{	
	openDiskAnalyze = new QAction(tr("File Explorer"), this);  
	openDiskAnalyze->setToolTip("File Explorer");	
	connect(openDiskAnalyze, SIGNAL(triggered()), this, SLOT(parseBatch()));	 

	openErrorAction = new QAction(tr("Show Errors"),this); 
	openErrorAction->setToolTip("Show Errors");
	connect(openErrorAction, SIGNAL(triggered()), this, SLOT(openSummaryErrorsWindow()));	 

	openCalendarAction = new QAction(tr("Calendar"),this); 
	openCalendarAction->setToolTip("Calendar");
	connect(openCalendarAction, SIGNAL(triggered()), this, SLOT(openCalendarWindow()));	

	openStructureAction = new QAction(tr("Issue viewer"),this); 
	openStructureAction->setToolTip("Issue viewer");
	connect(openStructureAction, SIGNAL(triggered()), this, SLOT(openStructureWindow()));

	openTitleCheck = new QAction(tr("Title check"),this); 
	openTitleCheck->setToolTip("Title check");
	connect(openTitleCheck, SIGNAL(triggered()), this, SLOT(openTitleCheckWindow()));

	openSelectBatch = new QAction(tr("Return"),this); 
	openSelectBatch->setToolTip("Return");
	connect(openSelectBatch, SIGNAL(triggered()), this, SLOT(openSelectBatchWindow()));

	openInventaire = new QAction(tr("Inventaire"),this); 
	openInventaire->setToolTip("Inventaire");
	connect(openInventaire, SIGNAL(triggered()), this, SLOT(openInventaireWindow()));


	fileTools = new QToolBar( "file toolbar",this);

	fileTools->addAction(openDiskAnalyze);
	fileTools->addAction(openErrorAction);
	fileTools->addAction(openCalendarAction);
	fileTools->addAction(openStructureAction);	
	
	if( batch.databaseInv !="")
	{
		fileTools->addAction(openInventaire);
	}
	fileTools->addAction(openTitleCheck);
	fileTools->addAction(openSelectBatch);	 
	fileTools->setAllowedAreas(Qt::TopToolBarArea );
	addToolBar(Qt::TopToolBarArea, fileTools);
}

void w_main::openSummaryErrorsWindow()
{
	w_errors *w = new w_errors();	
	w->setBatchDetail(batch);
	this->resize(1050,800);
	this->setCentralWidget(w); 
}

void w_main::openCalendarWindow()
{	
	w_calendar *cal = new w_calendar();
	cal->setBatchDetail(batch); 
	this->resize(1050,1020);
	this->setCentralWidget(cal); 		
}

void w_main::parseBatch()
{	
	w_disk *disk = new w_disk();
	disk->setBatchDetail(batch);	
	this->resize(1050,1020);
	this->setCentralWidget(disk); 
}

void w_main::openStructureWindow()
{
	w_structview *view = new w_structview();
	view->setBatchDetail(batch);	
	this->resize(1200,910);
	this->setCentralWidget(view);  
}

void w_main::openTitleCheckWindow()
{
	w_titlecheck *titlecheck = new  w_titlecheck();
	titlecheck->setBatchDetail(batch);
	this->resize(1050,910);
	this->setCentralWidget(titlecheck); 
}

void w_main::openSelectBatchWindow()
{ 
	w_selectBatch *gui = new w_selectBatch();
	gui->show();
	this->close();
}


void w_main::openInventaireWindow()
{	
	w_inventaire *invent = new w_inventaire();
	invent->setBatchDetail(batch);	
	this->resize(1050,910);
	this->setCentralWidget(invent); 
}
