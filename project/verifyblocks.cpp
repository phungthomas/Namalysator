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
				hError->getError(cat_multipleBlock,"METS","LOGICAL STRUCT",element.first + " - " + element.second + " used multiple times",fileName,element.second);
			}
			else
			{
				block.insert(element);						
			}
		}

		browseItem(currentItem);				
	}
}

//Semantic checks verify :  Multiple block use
verifyblocks::verifyblocks(datafactory *dfverifiers,errorHandler *_hError,std::string &_fileName):hError(_hError),fileName(_fileName)
{	
	hError->begin("Verify: multiple block use");

	Item *item = dfverifiers->get<Item>("Item");	
	browseItem(item);	

}