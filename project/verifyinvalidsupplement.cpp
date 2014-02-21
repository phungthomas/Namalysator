#include "verifyinvalidsupplement.h"
#include "errorhandler.h"

const char* string_issue = "MODSMD_ISSUE";
const char* string_find = "MODSMD_SUPPLEMENT";

verifyinvalidsupplement::verifyinvalidsupplement(datafactory *dfVerifiers,ErrorHandler *hError,std::string &fileName)
{
	hError->begin("Verify: invalid supplement");
	datafactory_set<dmdsec> dfIssue = dfVerifiers->get_set<dmdsec>();
	std::string title;
	//search in Dmdsec
	datafactory_set<dmdsec> dftitles = dfVerifiers->get_set<dmdsec>();
	for (datafactory_set<dmdsec>::iterator it = dftitles.begin(); it != dftitles.end(); ++it)
	{	
		if (it.key().find(string_find)!=string::npos)
		{		
			for (std::map<std::string,std::string>::iterator it2 = it->mapAddStringData.begin(); it2 != it->mapAddStringData.end(); ++it2)
			{
				std::string titleSuppl ="";	
				std::string state = it2->first;
				if (state =="MODS:title")
				{			
					titleSuppl =  it2->second;					
				
					if (title == titleSuppl)
					{			
						hError->getError(cat_invalidSupplement,"METS","DMDSEC","DMDSEC : Title of " + it.key() + " is " + title ,fileName,it.key());		
					}	
				}
			}
		}
	}		
	//search in Logical Struct
	datafactory_set<Article> dfArticle = dfVerifiers->get_set<Article>();
	for (datafactory_set<Article>::iterator it = dfArticle.begin(); it != dfArticle.end(); ++it)
	{
		if (it.key().find(string_find)!=string::npos)
		{
			if (it->title == title)
			{				
				hError->getError(cat_invalidSupplement,"METS","LOGICAL STRUCT","LOGICAL STRUCT : Title of " + it.key() + " is " + title ,fileName,it->div);		
			}
		}
	}	
}