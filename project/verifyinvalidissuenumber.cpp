#include "verifyinvalidissuenumber.h"
#include <string>
#include <iostream>


verifyinvalidissuenumber::verifyinvalidissuenumber(datafactory *df,errorHandler *h,const std::string &fileName)
{
	h->begin("Verify: partnumber");
	Mets *mets = 0;
	mets = df->get<Mets>("METS");		
	if(mets->issueNumber.substr(0,3) != "Jg.")
	{
		h->getError(cat_invalidIssueNumber,"METS","DMDSEC",mets->issueNumber,fileName,mets->issueNumber);
	}
}