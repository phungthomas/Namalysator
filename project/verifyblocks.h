#ifndef VERIFYBLOCKS_H_
#define VERIFYBLOCKS_H_

#include "datafactory.h"
#include "errorhandler.h"

//! Semantic checks verify :  Multiple alto block use
class verifyblocks
{
private :
	std::set<std::pair<std::string, std::string>> block;
	errorHandler *hError;
	std::string fileName;

	void browseItem(Item * item);

public:
	verifyblocks(datafactory *df,errorHandler *h,std::string &fileName);
};


#endif	//VERIFYBLOCKS_H_