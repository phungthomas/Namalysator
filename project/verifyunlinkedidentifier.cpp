#include "verifyunlinkedidentifier.h"
#include <set>


verifyunlinkedidentifier::verifyunlinkedidentifier(datafactory *dfverifiers,ErrorHandler *hError,std::string &fileName)
{
	hError->begin("Verify: unlinked identifier");
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
				if (block.find(element)== block.end())
				{
					block.insert(element);						
				}
			}
		}
	}
 	datafactory_set<altoblock> dfaltoblock= dfverifiers->get_set<altoblock>();
	for (datafactory_set<altoblock>::iterator it = dfaltoblock.begin(); it != dfaltoblock.end(); ++it)
	{
		for (std::map<std::string,Block>::iterator it2 = it->mapalto.begin(); it2 != it->mapalto.end(); ++it2)
		{
			std::pair<std::string,std::string> element;
			element.first = it.key();
			element.second = it2->first;		
			if(block.find(element)!= block.end())
			{
				block.erase(element);
			}
		}
	}
	if (block.size() != 0)
	{
		for (size_t i=0 ; i< block.size(); i++)
		{
			for (set<std::pair<std::string,std::string>>::iterator it = block.begin(); it != block.end(); it++)
			{		
				hError->getError(cat_unlinkedIdentifier,"METS","Logical Struct",it->first + " - " + it->second ,fileName,it->second);
			}
		}
	}
}


