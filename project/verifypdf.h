#ifndef VERIFYPDF_H_
#define VERIFYPDF_H_

#include <string>
#include "datafactory.h"
#include "errorhandler.h"
#include <set>

//!verify if the PDF files exist and have the right sequence
class verifypdf
{

public:
	verifypdf(datafactory *df,ErrorHandler *h,std::string &pathdirectory);
};


#endif	//VERIFYIDENTIFIERMIX_H_