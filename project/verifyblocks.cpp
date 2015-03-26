#include "verifyblocks.h"
#include <set>
#include <vector>
#include <map>
#include <iostream>


void verifyblocks::browseItem(Item * item){
	Item * currentItem;
	for (size_t i=0; i< item->children.size();i++)
	{		
		currentItem = &item->children[i];

		for(size_t j=0;j < currentItem->vectTypeBlock.size();j++)
		{
			std::pair<std::string, std::string> element;
			element.first = currentItem->vectTypeBlock[j].alto;
			element.second = currentItem->vectTypeBlock[j].block;

			if (block.find(element)!= block.end())
			{						
				if (warnWhenMultipleBlockUse == 1 ) hError->getError(cat_multipleBlock,"METS","LOGICAL STRUCT",element.first + " - " + element.second + " used multiple times",fileName,element.second);
			}
			else
			{
				block.insert(element);						
			}
		}

		browseItem(currentItem);				
	}
}

void verifyblocks::checkUnlinkedIdentifier(){

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

//Semantic checks verify :  Multiple block use and unlinked identifier
verifyblocks::verifyblocks(datafactory *_dfverifiers,errorHandler *_hError,std::string &_fileName,int _warnWhenMultipleBlockUse):hError(_hError),fileName(_fileName),warnWhenMultipleBlockUse(_warnWhenMultipleBlockUse),dfverifiers(_dfverifiers)
{	
	//hError->begin("Verify: multiple block use");
	hError->begin("Verify: unlinked identifier");

	Item *item = dfverifiers->get<Item>("Item");	
	browseItem(item);
	checkUnlinkedIdentifier();

}