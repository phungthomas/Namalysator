#ifndef VERIFYALTOBLOCKPERPAGE_H_
#define VERIFYALTOBLOCKPERPAGE_H_

#include <string>
#include "datafactory.h"
#include "errorhandler.h"


//! verify if the number of blocks per page  > 0 
class verifyaltoblockperpage
{
private :
	std::set<std::pair<std::string, std::string>> block;	

public:
	verifyaltoblockperpage(datafactory *dfverifiers,errorHandler *hError,std::string &fname);
};


#endif	//VERIFYALTOBLOCKPERPAGE_H_