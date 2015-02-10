#include "w_report.h"
#include "structgui.h"
#include "bookModel.h"
#include <sstream>
w_report::w_report(QWidget *parent):QWidget(parent){
}

w_report::~w_report(){
}


void w_report::init(){
	QVBoxLayout* layv=new QVBoxLayout();
	QHBoxLayout* lay=new QHBoxLayout();
	layv->addLayout(lay);
	
	QLabel* lab=new QLabel("rate of completude:");
	lay->addWidget(lab);
	report=new QLabel("Unknown");
	lay->addWidget(report);
	lay->addStretch();

	lay=new QHBoxLayout();
	layv->addLayout(lay);
	lab=new QLabel("checked:");
	lay->addWidget(lab);
	labCheckCount=new QLabel("Unknown");
	lay->addWidget(labCheckCount);
	lay->addStretch();

	lay=new QHBoxLayout();
	layv->addLayout(lay);
	lab=new QLabel("total:");
	lay->addWidget(lab);
	labTot=new QLabel("Unknown");
	lay->addWidget(labTot);
	lay->addStretch();

	QTableView* qttable = new QTableView();
	bookModelInventory* book = new bookModelInventory(db);
	book->init();

	QSortFilterProxyModel*	proxyModel = new QSortFilterProxyModel();
	proxyModel->setSourceModel(book);

	qttable->setModel(proxyModel);
	qttable->verticalHeader()->hide();
	qttable->setEditTriggers(QAbstractItemView::NoEditTriggers);  
    qttable->setSelectionMode(QAbstractItemView::SingleSelection);  
    qttable->setSelectionBehavior(QAbstractItemView::SelectRows);  
	qttable->setAlternatingRowColors(true);
	qttable->setShowGrid(false);
	qttable->setSortingEnabled(true);
	qttable->resizeColumnsToContents();
	qttable->resizeRowsToContents();

	
	layv->addWidget(qttable);


	//layv->addStretch();
	setLayout(layv);
}

void w_report::setBatchDetail(){
	db.setDataBaseName(BatchDetail::getBatchDetail().database);
	std::vector<int> vect = db.getReport();
	if ( vect.size()==2 ){
		setValue ( vect [0], vect[0]+vect[1] );
	}else{
		setValue (0,0);
	}

}

void w_report::setValue(int i, int tot){
	double rate;
	std::stringstream ssi;
	std::stringstream sstot;
	std::stringstream ssrate;

	if ( tot != 0 ){
		ssi << i;
		sstot << tot;
		rate = 100.00*i/tot;
		ssrate << rate << "%";
	}else{
		ssi << "N/A";
		sstot << tot;
		ssrate << "N/A";
	}

	labCheckCount->setText(ssi.str().c_str());
	labTot->setText(sstot.str().c_str());
	report->setText(ssrate.str().c_str());
}


