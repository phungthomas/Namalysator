#include "w_booklist.h"
#include "itemdelegate.h"
#include <QModelIndex>

w_booklist::w_booklist(dbrequest & _db,QWidget *parent):db(_db),QWidget(parent){
	//init();
}

w_booklist::~w_booklist(){
}

void w_booklist::init(bool _sampling){
	sampling=_sampling;
	_mainLayout = new QVBoxLayout();
	this->setLayout(_mainLayout);
	bookView= new QTableView();
	_mainLayout->addWidget ( bookView );

	_bookModel = new bookModelE(db);
	_bookModel->init(sampling);
	proxyModel = new QSortFilterProxyModel();
	proxyModel->setSourceModel(_bookModel);

	bookView->setModel(proxyModel);
	bookView->verticalHeader()->hide();
	//bookView->setEditTriggers(QAbstractItemView::NoEditTriggers);  
    bookView->setSelectionMode(QAbstractItemView::SingleSelection);  
    bookView->setSelectionBehavior(QAbstractItemView::SelectRows);  
	bookView->setAlternatingRowColors(true);
	ComboBoxItemDelegate* delegate=new ComboBoxItemDelegate(db);
	bookView->setItemDelegateForColumn(0,delegate);
	bookView->setShowGrid(false);
  	bookView->setHorizontalHeader(new bookColumn(Qt::Horizontal));
	bookView->setSortingEnabled(true);
	bookView->sortByColumn(1);
	bookView->resizeColumnsToContents();
	bookView->resizeRowsToContents();

	connect ( bookView, SIGNAL(clicked(QModelIndex)), this, SLOT(onclick(QModelIndex)));
}

void w_booklist::samplingSelection(){
	sampling = true;
	reload();
}
void w_booklist::allSelection(){
	sampling = false;
	reload();
}

void w_booklist::reload(){
	_bookModel->init(sampling);
}


void w_booklist::onclick(const QModelIndex & idx){
	int metsId = _bookModel->idMets(proxyModel->mapToSource(idx));
	if ( idx.column()  != 4 ) {
		emit metsIdSelected( metsId );
	} else {
		emit metsThumb( metsId );
		//emit metsIdSelected( metsId );
	}
}