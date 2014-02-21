#ifndef VERIFYODDSPAGES_H_
#define VERIFYODDSPAGES_H_

#include <string>
#include "errorhandler.h"

//! verify  if the number of pages are odds or even
class verifyoddspages
{
	public:
		verifyoddspages(ErrorHandler *h,const std::string &currentMetsFile,const int &size);
};

#endif	//VERIFYODDSPAGES_H_

