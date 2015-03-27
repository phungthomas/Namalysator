#include "w_main.h"
#include "ui_w_main.h"
#include "odswriter.h"
#include "w_disk.h"
#include "w_calendar.h"
#include "w_structview.h"
//#include "w_titlecheck.h"
#include "w_errors.h"
#include "w_exportdata.h"
#include "qwidgettaberror.h"
#include "w_selectbatch.h"
#include "w_errors.h"
#include "exportdata.h"
#include "w_thumb.h"
#include "w_report.h"
#include "w_entitycount.h"
#include "exportDataHelper.h"
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

	openSelectBatch = menu->addAction(QIcon("open-file-icon.png"),tr("Select batch")); 
	openSelectBatch->setToolTip("Select batch");
	connect(openSelectBatch, SIGNAL(triggered()), this, SLOT(openSelectBatchWindow()));

	QAction * act = menu->addAction(tr("Export Title Data"));
	connect(act, SIGNAL(triggered()), this, SLOT(exportData()));

	menu->addSeparator();

	act = menu->addAction(tr("Exit"));
	connect(act, SIGNAL(triggered()), this, SLOT(exit()));

	menu = menuBar->addMenu("View"); 

	openDiskAnalyze = menu->addAction(QIcon("dos-application-icon.png"),tr("File Explorer"));  
	openDiskAnalyze->setToolTip("File Explorer");	
	connect(openDiskAnalyze, SIGNAL(triggered()), this, SLOT(parseBatch()));

	openErrorAction =  menu->addAction(QIcon("Emoticon-Shocked-Screaming-Scream-icon.png"),tr("Show Errors"));
	openErrorAction->setToolTip("Show Errors");
	connect(openErrorAction, SIGNAL(triggered()), this, SLOT(openSummaryErrorsWindow()));	 

	openCalendarAction = menu->addAction(tr("Calendar"));
	openCalendarAction->setToolTip("Calendar");
	connect(openCalendarAction, SIGNAL(triggered()), this, SLOT(openCalendarWindow()));	

	openStructureAction = menu->addAction(QIcon("Emoticon-Hiding-Scared-icon.png"),tr("Issue viewer")); 
	openStructureAction->setToolTip("Issue viewer");
	connect(openStructureAction, SIGNAL(triggered()), this, SLOT(openStructureWindow()));

	//openTitleCheck = menu->addAction(tr("Title check")); 
	//openTitleCheck->setToolTip("Title check");
	//connect(openTitleCheck, SIGNAL(triggered()), this, SLOT(openTitleCheckWindow()));

	menu = menuBar->addMenu("Report");

	act = menu->addAction(QIcon("Sales-report-icon.png"),tr("Completeness of campaign"));
	connect(act, SIGNAL(triggered()), this, SLOT(openReport()));
	act = menu->addAction(tr("Total of entity"));
	connect(act, SIGNAL(triggered()), this, SLOT(openEntityCount()));

}

void w_main::openEntityCount (){

	w_entitycount *w = new w_entitycount();	

	
	w->setBatchDetail();
	w->init();

	titleChange("Entity Count");
	this->resize(900,200);
	this->setCentralWidget(w); 

}

void w_main::openReport()
{
	w_report *w = new w_report();	

	w->init();
	w->setBatchDetail();

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
	this->resize(1050,910);
	this->setCentralWidget(disk); 
}

void w_main::openStructureWindow()
{
	w_structview *view = new w_structview();
	view->setBatchDetail();	
	view->setQMainWindow(this);
	titleChange("Issue Viewer");
	this->resize(1200,910);
	view->setMinimumHeight(700);
	this->setCentralWidget(view); 
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




void w_main::exportData(){

	QString fileName = QFileDialog::getSaveFileName(this,tr("Open File"),"",tr("file (*.ods)"));
    std::string message;

	if (!fileName.isEmpty()) 
    {		
		message = fileName.toStdString();
    };

	exportDataHelper helper;
	helper.exportData(message,this);


	QMessageBox::information(this, tr("Namalysator"),
                                   tr("Export finished"));
}




