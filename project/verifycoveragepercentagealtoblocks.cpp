#include "verifycoveragepercentagealtoblocks.h"
#include "errorhandler.h"
#include <map>
#include <iostream>
#include <sstream>

verifycoveragepercentagealtoblocks::verifycoveragepercentagealtoblocks(datafactory *dfverifiers,errorHandler *hError,std::string &fname,PhysicalLogicalAltoFilter& _filter,int ratio):filter(_filter)
{

	bool supplement= false;
	datafactory_set<dmdsec> dfissue = dfverifiers->get_set<dmdsec>();
	for (datafactory_set<dmdsec>::iterator it = dfissue.begin(); it != dfissue.end(); ++it)
	{		
		if (it.key().find("MODSMD_SUPPLEMENT")!=string::npos)
		{	
			supplement = true;	
			break;		
		}
	}
	
	datafactory_set<altoblock> dfaltoblock= dfverifiers->get_set<altoblock>();
	for (datafactory_set<altoblock>::iterator it = dfaltoblock.begin(); it != dfaltoblock.end(); ++it)
	{	
		float sumArea = it->printSpaceHeight * it->printSpaceWidth;
		float sumAreaArticle = 0;	

		

		if ( ! filter.isAltoToCheck ( it.key() ) ) continue; // skip the one to not test
		//std::cout << "KEY:" << it.key() <<std::endl;

		for (std::map<std::string,Block>::iterator it2 = it->mapalto.begin(); it2 != it->mapalto.end(); ++it2)
		{	
			
			sumAreaArticle = sumAreaArticle +  it2->second.height * it2->second.width;
		}
		//std::cout << " sum area article = " << sumAreaArticle << std::endl;
		float percentage = sumAreaArticle / sumArea * 100;
		std::stringstream o;
		o << percentage;	
		if (percentage <= ratio &&	supplement == false )
		{	
			std::stringstream mess;
			mess << "actual coverage :" + o.str() + " is under "<<ratio<<"% ";
			hError->getError(cat_actualcoverage,"LINKEDFILES",it.key(),mess.str(),it.key(),"");		
		
			#ifdef _DEBUG
				std::cout << it.key() <<" " << o.str()  << " is under 75% " << std::endl;
			#endif // DEBUG
		}	
	}
}
