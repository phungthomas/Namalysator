#include "w_entitycount.h"
#include "entitycountModel.h"


void w_entitycount::setBatchDetail(){
	db.setDataBaseName(BatchDetail::getBatchDetail().database);
}

w_entitycount::w_entitycount(QWidget *parent):QWidget(parent){
}

w_entitycount::~w_entitycount(){
}

void w_entitycount::init(){
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

	setLayout(mainLayout);
}