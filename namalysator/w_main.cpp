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
#include "w_thumb.h"
#include <iostream>

std::string w_main::title;

w_main::w_main(QWidget *parent) :
QMainWindow(parent),
m_ui(new Ui::w_main)
{
	m_ui->setupUi(this);    
}

void w_main::setBatchDetail()
{ 
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
	newsPaperActions();
}


void w_main::newsPaperActions()
{	
	QMenuBar* menuBar = this->menuBar();
	//menuBar->hide();
	QMenu* menu = menuBar->addMenu("File"); 

	openSelectBatch = menu->addAction(tr("Select batch")); 
	openSelectBatch->setToolTip("Select batch");
	connect(openSelectBatch, SIGNAL(triggered()), this, SLOT(openSelectBatchWindow()));

	QAction * act = menu->addAction(tr("Exit"));
	connect(act, SIGNAL(triggered()), this, SLOT(exit()));

	menu = menuBar->addMenu("Tool"); 

	openDiskAnalyze = menu->addAction(tr("File Explorer"));  
	openDiskAnalyze->setToolTip("File Explorer");	
	connect(openDiskAnalyze, SIGNAL(triggered()), this, SLOT(parseBatch()));

	openErrorAction =  menu->addAction(tr("Show Errors"));
	openErrorAction->setToolTip("Show Errors");
	connect(openErrorAction, SIGNAL(triggered()), this, SLOT(openSummaryErrorsWindow()));	 

	openCalendarAction = menu->addAction(tr("Calendar"));
	openCalendarAction->setToolTip("Calendar");
	connect(openCalendarAction, SIGNAL(triggered()), this, SLOT(openCalendarWindow()));	

	openStructureAction = menu->addAction(tr("Issue viewer")); 
	openStructureAction->setToolTip("Issue viewer");
	connect(openStructureAction, SIGNAL(triggered()), this, SLOT(openStructureWindow()));

	openTitleCheck = menu->addAction(tr("Title check")); 
	openTitleCheck->setToolTip("Title check");
	connect(openTitleCheck, SIGNAL(triggered()), this, SLOT(openTitleCheckWindow()));
	
	if( BatchDetail::getBatchDetail().databaseInv !="")
	{
		openInventaire = menu->addAction(tr("Inventaire"));
		openInventaire->setToolTip("Inventaire");
		connect(openInventaire, SIGNAL(triggered()), this, SLOT(openInventaireWindow()));
	}

	menu = menuBar->addMenu("Report");

	act = menu->addAction(tr("Completeness of campaign"));
	connect(act, SIGNAL(triggered()), this, SLOT(openReport()));

}


void w_main::openReport()
{
	QWidget *w = new QWidget();	
	//w->setBatchDetail();
	QVBoxLayout* layv=new QVBoxLayout();
	QHBoxLayout* lay=new QHBoxLayout();
	layv->addLayout(lay);
	
	QLabel* lab=new QLabel("rate of completude:");
	lay->addWidget(lab);
	lab=new QLabel("0.3%");
	lay->addWidget(lab);
	lay->addStretch();

	lay=new QHBoxLayout();
	layv->addLayout(lay);
	lab=new QLabel("checked:");
	lay->addWidget(lab);
	lab=new QLabel("200");
	lay->addWidget(lab);
	lay->addStretch();

	lay=new QHBoxLayout();
	layv->addLayout(lay);
	lab=new QLabel("total:");
	lay->addWidget(lab);
	lab=new QLabel("2000");
	lay->addWidget(lab);
	lay->addStretch();

	layv->addStretch();
	w->setLayout(layv);
	titleChange("Completeness");
	this->resize(900,200);
	this->setCentralWidget(w); 
}


void w_main::openSummaryErrorsWindow()
{
	w_errors *w = new w_errors();	
	w->setBatchDetail();
	titleChange("Error Summary");
	this->resize(1050,800);
	this->setCentralWidget(w); 
}

void w_main::openCalendarWindow()
{	
	w_calendar *cal = new w_calendar();
	cal->setBatchDetail(); 
	titleChange("Calendar");
	this->resize(1050,1020);
	this->setCentralWidget(cal); 		
}

void w_main::parseBatch()
{	
	w_disk *disk = new w_disk();
	disk->setBatchDetail();
	titleChange("File Explorer");
	this->resize(1050,1020);
	this->setCentralWidget(disk); 
}

void w_main::openStructureWindow()
{
	w_structview *view = new w_structview();
	view->setBatchDetail();	
	titleChange("Issue Viewer");
	this->resize(1200,910);
	this->setCentralWidget(view); 
}

void w_main::openTitleCheckWindow()
{
	w_titlecheck *titlecheck = new  w_titlecheck();
	titlecheck->setBatchDetail();
	titleChange("Title Check");
	this->resize(1050,910);
	this->setCentralWidget(titlecheck); 
}


void w_main::openSelectBatchWindow()
{ 
	w_selectBatch *gui = new w_selectBatch();
	this->menuBar()->hide();
	titleChange("","Namalysator");
	this->resize(800,600);
	this->setCentralWidget(gui);

	connect(gui, SIGNAL(validated(std::string)), this, SLOT(openStart(std::string)));
	connect(gui, SIGNAL(exited()), this, SLOT(exit()));
}

void w_main::exit(){
	close();
}

void w_main::openStart(std::string date){
	menuBar()->show();
	titleChange("",BatchDetail::getBatchDetail().batchName +" on "+date);
	parseBatch();
}
void w_main::openInventaireWindow()
{	
	w_inventaire *invent = new w_inventaire();
	invent->setBatchDetail();	
	titleChange("Inventaire");
	resize(1050,910);
	setCentralWidget(invent); 
}


void w_main::modeNewsPaper()
{
	removeToolBar(fileTools);
	newsPaperActions();
}

void w_main::titleChange(std::string sub,std::string _title){
	title = _title;
	subTitle = sub; 
	std::string tmp=title + "     " + subTitle;
	this->setWindowTitle(tmp.c_str());
}