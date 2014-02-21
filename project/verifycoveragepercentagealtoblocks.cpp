#include "verifycoveragepercentagealtoblocks.h"
#include "errorhandler.h"
#include <map>
#include <iostream>
#include <sstream>

verifycoveragepercentagealtoblocks::verifycoveragepercentagealtoblocks(datafactory *dfverifiers,ErrorHandler *hError,std::string &fname)
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
	
	datafactory_set<Article> dfarticle = dfverifiers->get_set<Article>();
	
	datafactory_set<altoblock> dfaltoblock= dfverifiers->get_set<altoblock>();
	for (datafactory_set<altoblock>::iterator it = dfaltoblock.begin(); it != dfaltoblock.end(); ++it)
	{	
		float sumArea = it->printSpaceHeight * it->printSpaceWidth;
		float sumAreaArticle = 0;	
		for (std::map<std::string,Block>::iterator it2 = it->mapalto.begin(); it2 != it->mapalto.end(); ++it2)
		{	
			sumAreaArticle = sumAreaArticle +  it2->second.height * it2->second.width;
		}
		//std::cout << " sum area article = " << sumAreaArticle << std::endl;
		float percentage = sumAreaArticle / sumArea * 100;
		std::stringstream o;
		o << percentage;	
		if (percentage <= 75 &&	supplement == false )
		{			
			hError->getError(cat_actualcoverage,"LINKEDFILES",it.key(),"actual coverage :" + o.str() + " is under 75% ",it.key(),"");		
		
			#ifdef _DEBUG
				std::cout << it.key() <<" " << o.str()  << " is under 75% " << std::endl;
			#endif // DEBUG
		}	
	}
}
