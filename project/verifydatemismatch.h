#ifndef VERIFYDATEMISMATCH_H_
#define VERIFYDATEMISMATCH_H_

#include <string>
#include "datafactory.h"
#include "errorhandler.h"

//! verify if the date of issue equals name of mets file
class verifydatemismatch
{
	
public:
	verifydatemismatch::verifydatemismatch(errorHandler *hError,Mets *mets);
	
};



#endif	//VERIFYDATEMISMATCH_H_