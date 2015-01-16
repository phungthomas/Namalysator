#include "w_booklist.h"

w_booklist::w_booklist(QWidget *parent){
	init();
}

w_booklist::~w_booklist(){
}

void w_booklist::init(){
	_mainLayout = new QVBoxLayout();
	this->setLayout(_mainLayout);
	bookView= new QTableView();
	_mainLayout->addWidget ( bookView );

	_bookModel = new bookModel();
	proxyModel = new QSortFilterProxyModel();
	proxyModel->setSourceModel(_bookModel);

	bookView->setModel(proxyModel);
	bookView->verticalHeader()->hide();
	bookView->setAlternatingRowColors(true);
	bookView->setShowGrid(false);
	bookView->setHorizontalHeader(new bookColumn(Qt::Horizontal));
	bookView->setSortingEnabled(true);
}