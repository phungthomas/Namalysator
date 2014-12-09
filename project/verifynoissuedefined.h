#ifndef VERIFYNOISSUEDEFINED_H_
#define VERIFYNOISSUEDEFINED_H_

#include <string>
#include "datafactory.h"
#include "errorhandler.h"

//! verify if a issue is defined
class verifynoissuedefined
{	
public:
	verifynoissuedefined(datafactory *df,errorHandler *h,const std::string &fileName);
};

#endif	//VERIFYNOISSUEDEFINED_H_