#include "verifydivs.h"
#include "errorhandler.h"
//Data integrity : verify uniqueness of divs
verifydivs::verifydivs(datafactory *dfverifiers,ErrorHandler *hError,std::string &fileName)
{	
	hError->begin("Verify: Divs");
	datafactory_set<DivType> dfDivType = dfverifiers->get_set<DivType>();
	std::set<std::string> div;
	for (datafactory_set<DivType>::iterator it = dfDivType.begin(); it != dfDivType.end(); ++it)
	{
		for (size_t i =0;i< it->vectDivType.size();i++)
		{
			if (div.find(it->vectDivType[i].first)!= div.end())
			{				
				
				hError->getError(cat_multipleDiv,"METS","LOGICAL STRUCT",it->vectDivType[i].first + " - " + it->vectDivType[i].second,fileName,it->vectDivType[i].first);
			}
			else
			{
				div.insert(it->vectDivType[i].first);				
			}
		}
	}
}