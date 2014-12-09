#ifndef VERIFYCHECKSUM_H_
#define VERIFYCHECKSUM_H_

#include "datafactory.h"
#include "errorhandler.h"

//! verify checksum of files
class verifychecksum
{
	public:
		verifychecksum(datafactory *df,errorHandler *h,const std::string &fileName,const std::string &path);
};

#endif	//VERIFYCHECKSUM_H_