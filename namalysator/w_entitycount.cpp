#include "w_entitycount.h"

void w_entitycount::setBatchDetail(){
	db.setDataBaseName(BatchDetail::getBatchDetail().database);



}

w_entitycount::w_entitycount(QWidget *parent):QWidget(parent){
}

w_entitycount::~w_entitycount(){
}

void w_entitycount::init(){
	QVBoxLayout* layv=new QVBoxLayout();
	setLayout(layv);
}