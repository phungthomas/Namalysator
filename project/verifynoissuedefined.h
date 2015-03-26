#ifndef VERIFYNOISSUEDEFINED_H_
#define VERIFYNOISSUEDEFINED_H_

#include <string>
#include "datafactory.h"
#include "errorhandler.h"

//! verify if a issue is defined
class verifynoissuedefined
{	
	errorHandler *hError;
	bool findIssue;
	void browseItem(Item * item);
public:
	verifynoissuedefined(datafactory *df,errorHandler *h,const std::string &fileName);
};

#endif	//VERIFYNOISSUEDEFINED_H_