#include "verifynoissuedefined.h"


verifynoissuedefined::verifynoissuedefined(datafactory *dfVerifiers,ErrorHandler *hError,const std::string &fileName)
{
	hError->begin("Verify if issue defined ");
	bool findIssue =false;
	datafactory_set<Article> dfArticle = dfVerifiers->get_set<Article>();	
	for (datafactory_set<Article>::iterator it = dfArticle.begin(); it != dfArticle.end(); ++it)
	{
		if (it->type.find("ISSUE")!=string::npos)
		{
			findIssue =true;
			break;
		}		
	}	
	if(findIssue ==false)
	{
		hError->getError(cat_noIssueDefined,"METS","LOGICAL STRUCT",fileName,fileName,"");
	}
}
