#include "bookColumn.h"



bookColumn::bookColumn(Qt::Orientation orientation,QWidget * parent): QHeaderView(orientation,parent){
	this->setClickable(true);
}

bookColumn::~bookColumn(){
}

