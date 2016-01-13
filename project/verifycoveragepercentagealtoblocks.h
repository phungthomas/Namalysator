#ifndef VERIFYCOVERAGEPERCENTAGEALTOBLOCKS_H_
#define VERIFYCOVERAGEPERCENTAGEALTOBLOCKS_H_

#include <string>
#include "datafactory.h"
#include "errorhandler.h"
#include "physLogALTO.h"

//! Verify if the sum of the areas of the ALTO blocks divided by the total page size is > 75%
class verifycoveragepercentagealtoblocks
{
private :
	std::set<std::pair<std::string, std::string>> block;	
	PhysicalLogicalAltoFilter& filter;
public:
	verifycoveragepercentagealtoblocks(datafactory *df,errorHandler *h,std::string &fileName,PhysicalLogicalAltoFilter& _filter,int ratio=75);
};


#endif	//VERIFYCOVERAGEPERCENTAGEALTOBLOCKS_H_