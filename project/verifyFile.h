#ifndef VERIFYFILE_H_
#define VERIFYFILE_H_

#include <string>
#include "datafactory.h"
#include "errorhandler.h"
#include <set>

//!verify if the PDF files exist and have the right sequence
class verifyFile{
public:
	verifyFile(datafactory *df,errorHandler *h,std::string &pathdirectory,std::string TYPE);
};


#endif	//VERIFYIDENTIFIERMIX_H_