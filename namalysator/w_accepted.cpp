#include "w_accepted.h"
#include "structgui.h"


void acceptedW::change(bool val){

	emit changeHash ( val,hashkey ) ;

	/*
	if ( val) {
		db.insertAccepted(hashkey);	
	}else{
		db.deleteAccepted(hashkey);
	}
	*/

}

	
acceptedW::acceptedW( int _value,std::string _hash,QWidget * parent): QCheckBox(parent),value(_value), hashkey(_hash){
	this->setChecked(value == 0 ? false:true);
	connect ( this,SIGNAL(toggled ( bool )), this, SLOT(change(bool)) );
};