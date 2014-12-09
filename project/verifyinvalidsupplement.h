#ifndef VERIFYINVALIDSUPPLEMENT_H_
#define VERIFYINVALIDSUPPLEMENT_H_

#include <string>
#include "datafactory.h"
#include "errorhandler.h"

//! verify if the title of newspaper is different of the title of supplement
class verifyinvalidsupplement
{
private :
	std::set<std::pair<std::string, std::string>> block;	

public:
	verifyinvalidsupplement(datafactory *df,errorHandler *h,std::string &fileName);
};


#endif	//VERIFYINVALIDSUPPLEMENT_H_