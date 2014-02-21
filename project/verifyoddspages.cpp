#include "verifyoddspages.h"
#include <sstream>

//verify if pages are odd or even
verifyoddspages::verifyoddspages(ErrorHandler *hError,const std::string &currentMetsFile,const int &size)
{
	hError->begin("Verify : odds pages");
	if (size % 2 != 0)
	{		
		std::stringstream ss;
		ss << size;
		hError->getError(cat_odds,"METS",currentMetsFile,ss.str(), currentMetsFile,"");		
	}
}