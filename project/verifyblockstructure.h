#ifndef VERIFYBLOCKSTRUCTURE_H_
#define VERIFYBLOCKSTRUCTURE_H_

#include <string>
#include "datafactory.h"
#include "errorhandler.h"


//! verify the structure of blocks
class verifyblockstructure
{
	private :
		std::set<std::pair<std::string, std::string>> block;	

	public:
		verifyblockstructure(datafactory *dfVerifiers,errorHandler *hError,const std::string &fName);
	};


#endif	//VERIFYBLOCKSTRUCTURE_H_