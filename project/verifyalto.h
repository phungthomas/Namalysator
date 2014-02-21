#ifndef VERIFYALTO_H_
#define VERIFYALTO_H_

#include "errorhandler.h"
#include <set>

//!verify if the ALTO files exist and have the right sequence
class verifyalto
{
private :
	std::set<std::pair<std::string, std::string>> block;	

public:
	verifyalto(datafactory *dfverifiers,ErrorHandler *hError,std::string &pathdirectory);
};


#endif	//VERIFYALTO_H_