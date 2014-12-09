#ifndef VERIFYDIVS_H_
#define VERIFYDIVS_H_

#include <string>
#include "datafactory.h"
#include "errorhandler.h"


//! verify uniqueness of divs
class verifydivs
{
	public:
		verifydivs(datafactory *df,errorHandler *h,std::string &fileName);
};

#endif	//VERIFYDIVS_H_