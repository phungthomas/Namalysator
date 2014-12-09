#ifndef VERIFYDATEFOLDER_H_
#define VERIFYDATEFOLDER_H_

#include <string>
#include "errorhandler.h"

//! Verify if name(date) of folder equals name(date) of Metsfile
class verifydatefolder
{
	public:
		verifydatefolder(errorHandler *h,std::string &fileName,std::string &path);
};

#endif	//VERIFYDATEFOLDER_H_

