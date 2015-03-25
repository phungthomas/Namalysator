#ifndef TITLETOCHECK_H_
#define TITLETOCHECK_H_

#include <string>
#include "datafactory.h"
#include "errorhandler.h"

//! verify if the title must be checked manually 
class titletocheck
{

public:
	titletocheck(datafactory *dfverifiers,errorHandler *hError);
private: 
	datafactory *dfverifiers;

};


#endif	//TITLETOCHECK_H_



