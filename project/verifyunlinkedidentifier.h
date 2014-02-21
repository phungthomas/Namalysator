#ifndef VERIFYUNLINKEDIDENTIFIER_H_
#define VERIFYUNLINKEDIDENTIFIER_H_

#include <string>
#include "datafactory.h"
#include "errorhandler.h"

//! Data integrity : verify if all blocks in alto are linked from the logical structure.
class verifyunlinkedidentifier
{
	private :
		std::set<std::pair<std::string, std::string>> block;	
	public:
		verifyunlinkedidentifier(datafactory *df,ErrorHandler *h,std::string &fileName);
};
#endif	//VERIFYUNLINKEDIDENTIFIER_H_