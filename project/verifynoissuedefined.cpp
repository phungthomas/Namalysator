#include "verifynoissuedefined.h"


void verifynoissuedefined::browseItem(Item * item){
	Item * currentItem;
	for (size_t i=0; i< item->children.size();i++)
	{		
		currentItem = &item->children[i];

		if ( currentItem->type.find("ISSUE")!=string::npos )findIssue = true;

		if ( findIssue ) return;

		browseItem(currentItem);				
	}
}

verifynoissuedefined::verifynoissuedefined(datafactory *dfverifiers,errorHandler *_hError,const std::string &fileName):hError(_hError)
{
	hError->begin("Verify if issue defined ");
	findIssue =false;

	Item *item = dfverifiers->get<Item>("Item");
	browseItem(item);
	
	if(findIssue ==false)
	{
		hError->getError(cat_noIssueDefined,"METS","LOGICAL STRUCT",fileName,fileName,"");
	}
}
