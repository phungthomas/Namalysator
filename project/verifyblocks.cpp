#include "verifyblocks.h"
#include <set>
#include <vector>
#include <map>
#include <iostream>

//Semantic checks verify :  Multiple block use
verifyblocks::verifyblocks(datafactory *dfverifiers,ErrorHandler *hError,std::string &fileName)
{	
	hError->begin("Verify: multiple block use");
	datafactory_set<Article> dfArticle = dfverifiers->get_set<Article>();	
	for (datafactory_set<Article>::iterator it = dfArticle.begin(); it != dfArticle.end(); ++it)
	{
		if (it->type.find("ISSUE")==0)
		{		
			for (size_t i =0;i< it->vectArticle.size();i++)
			{
				std::pair<std::string, std::string> element;
				element.first = it->vectArticle[i].alto;
				element.second = it->vectArticle[i].block;
	
				if (block.find(element)!= block.end())
				{						
					#ifdef _DEBUG
						std::cout << "multiple use " << it->vectArticle[i].alto << " - " << it->vectArticle[i].block <<std::endl;					
					#endif // DEBUG
					hError->getError(cat_multipleBlock,"METS","LOGICAL STRUCT",element.first + " - " + element.second + " used multiple times",fileName,element.second);
				}
				else
				{
					block.insert(element);						
				}
			}
			break;
		}			
	}
}