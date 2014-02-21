#ifndef VERIFYISSUENUMBER_H_
#define VERIFYISSUENUMBER_H_


#include "datafactory.h"
#include "errorhandler.h"

//! verify if the issue number has the good format
class verifyinvalidissuenumber
{
	public:
		verifyinvalidissuenumber(datafactory *df,ErrorHandler *h,const std::string &fileName);
};



#endif	//VERIFYISSUENUMBER_H_