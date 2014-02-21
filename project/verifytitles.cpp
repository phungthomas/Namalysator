#include "verifytitles.h"
#include "errorhandler.h"
#include <map>
#include <iostream>

const char* unknown = "UNKNOWN";


verifytitles::verifytitles(datafactory *dfverifiers,ErrorHandler *hError,std::string &fileName)
{
	hError->begin("Verify: Titles");
/*		
	datafactory_set<dmdsec> dftitles = dfverifiers->get_set<dmdsec>();
	for (datafactory_set<dmdsec>::iterator it = dftitles.begin(); it != dftitles.end(); ++it)
	{			
		for (std::map<std::string,std::string>::iterator it2 = it->mapAddStringData.begin(); it2 != it->mapAddStringData.end(); ++it2)
		{						
			if (it2->second.find(unknown) != std::string::npos)
			{
				#ifdef _DEBUG
					std::cout << it.key() + " contains the disallowed word : " + std::string(unknown) <<std::endl;
				#endif // DEBUG			
			}				
		}
	}	
*/	
	datafactory_set<Article> dfArticle = dfverifiers->get_set<Article>();
	for (datafactory_set<Article>::iterator it = dfArticle.begin(); it != dfArticle.end(); ++it)
	{
		if (it->title.find(unknown) != std::string::npos)
		{
			#ifdef _DEBUG
					std::cout << it.key() + " contains the disallowed word : " + std::string(unknown) <<std::endl;
				#endif // DEBUG			
			//	hError->getError(cat_wrongTitle,"METS","DMDSEC",it.key() + " contains the disallowed word : " + std::string(unknown),fileName);		
				hError->getError(cat_wrongTitle,"METS","DMDSEC",it.key() + " contains the disallowed word : " + std::string(unknown),fileName,it->div);		
			
		}
	
	}
	
}
