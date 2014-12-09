#ifndef VERIFYIMG_H_
#define VERIFYIMG_H_

#include <string>
#include "datafactory.h"
#include "errorhandler.h"
#include <set>

//!verify if the IMAGE files exist and have the right sequence
class verifyimg
{
private :
	std::set<std::pair<std::string, std::string>> block;	
	
public:
	verifyimg(datafactory *dfverifiers,errorHandler *hError,std::string &pathdirectory);
};


#endif	//VERIFYIMG_H_