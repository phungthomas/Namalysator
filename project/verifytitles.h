#ifndef VERIFYTITLES_H_
#define VERIFYTITLES_H_

#include "datafactory.h"
#include "errorhandler.h"

//! verify if the word UNKNOWN is in the title
class verifytitles 
{
	public:
		verifytitles(datafactory *df,ErrorHandler *h,std::string &fileName);
};


#endif	//VERIFYTITLES_H_