#ifndef VERIFYMISSINGISSUE_H_
#define VERIFYMISSINGISSUE_H_

#include <string>
#include "datafactory.h"
#include "errorhandler.h"
#include <set>

//! verify if the issues are missing or not
class verifymissingissue
{
private:
	int before ;
	int after ;
	int current;
	std::set<std::pair<std::string, int>> ErrorIssue;	
public:
	verifymissingissue(ErrorHandler *hError,database *db);
};

#endif	//VERIFYMISSINGISSUE_H_