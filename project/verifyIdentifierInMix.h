#ifndef VERIFYIDENTIFIERMIX_H_
#define VERIFYIDENTIFIERMIX_H_

#include <string>
#include "datafactory.h"
#include "errorhandler.h"

//! verify administrative metadata ID from logical structure

class verifyidentifierinmix
{
	public:
		verifyidentifierinmix(datafactory *df,errorHandler *h,std::string &fileName);
};
#endif	//VERIFYIDENTIFIERMIX_H_