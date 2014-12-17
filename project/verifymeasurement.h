#ifndef VERIFYMEASUREMENT_H_
#define VERIFYMEASUREMENT_H_

#include "datafactory.h"
#include "errorhandler.h"

class verifyMeasurement {
public : 
	verifyMeasurement(datafactory *dfverifiers,errorHandler *hError,std::string &fname);
};

#endif
