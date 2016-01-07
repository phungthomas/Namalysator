#include "w_entitycount.h"
#include "entitycountModel.h"


void w_entitycount::setBatchDetail(){
	db.setDataBaseName(BatchDetail::getBatchDetail().database);
}

w_entitycount::w_entitycount(QWidget *parent):QWidget(parent){
	menu = 0;
}

w_entitycount::~w_entitycount(){
	if ( menu ) {
		delete menu;
	}
	menu = 0;

}

void w_entitycount::init(QMainWindow* _qmain){
	qmain = _qmain;
	QVBoxLayout* mainLayout=new QVBoxLayout();

	QTableView* entityView= new QTableView();
	mainLayout->addWidget(entityView);

	entityCountModel* entityModel = new entityCountModel(db);
	entityModel->init();
	QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel();
	proxyModel->setSourceModel(entityModel);

	entityView->setModel(proxyModel);
	entityView->verticalHeader()->hide();
	entityView->setEditTriggers(QAbstractItemView::NoEditTriggers);  
    entityView->setSelectionMode(QAbstractItemView::SingleSelection);  
    entityView->setSelectionBehavior(QAbstractItemView::SelectRows);  
	entityView->setAlternatingRowColors(true);	
	entityView->setShowGrid(false);
	entityView->setSortingEnabled(true);
	entityView->resizeColumnsToContents();
	entityView->resizeRowsToContents();

	menu = qmain->menuBar()->addMenu("Total Entity Option"); 
	QAction *act = menu->addAction(tr("Export"));
	connect(act,SIGNAL(triggered()),this,SLOT(exportToFile()));

	setLayout(mainLayout);
}

void w_entitycount::exportToFile(){
	QString fileName = QFileDialog::getSaveFileName(this,tr("Open File"),"",tr("file (*.csv)"));
    std::string message;

	if (!fileName.isEmpty()) 
    {		
		message = fileName.toStdString();
	}else{
		return;
	};

	QMessageBox::information(this, tr("Namalysator"),
                                   tr((message+" Export to csv finished").c_str()));

}