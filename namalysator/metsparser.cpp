#include "metsparser.h"
#include "gui_utilities.h"

metsParser::metsParser(std::string &mets_fname,Item *itemtree)
{
	metsfile = mets_fname;
	currentstate = root;
	currentItem =0;
	rootItem = itemtree;
	counter=0;	
}

void metsParser::XMLstartElement(const char *name, const char **atts)
{	
	if (currentstate == root)
	{	
		if (strcmp(name,"structMap") == 0)
		{		
			std::string val = get_named_attr("TYPE", atts);	
			if (val.find("LOGICAL")!=std::string::npos)
			{		
				currentstate = logical;		
			}
		}
	}
	else if (currentstate == logical)
	{					
		const char *val1 = get_named_attr("ID", atts);
		const char *val2 = get_named_attr("TYPE", atts);
		const char *val3 = get_named_attr("LABEL", atts);
		const char *val4 = get_named_attr("DMDID", atts);	

		if (strcmp(name,"div")==0)
		{	
			if (currentItem ==0)
			{		
				rootItem = new Item;
				rootItem->counter = counter;
				rootItem->id = (val1 ? val1 : "");
				rootItem->label = (val3 ? val3 : "");
				rootItem->type = (val2 ? val2 : "");
				rootItem->dmdId = (val4 ? val4 : "");

				currentItem = rootItem;

				counter++;
			}
			else
			{	
				Item c;		
				c.counter = counter;		
				c.id = (val1 ? val1 : "");
				c.label = (val3 ? val3 : "");
				c.type = (val2 ? val2 : "");
				c.dmdId = (val4 ? val4 : "");
				c.parent = currentItem; 
				currentItem->children[currentItem->children.size()] = c;
				currentItem = &currentItem->children[currentItem->children.size()-1];	

				counter++;		
			}
		}	
		else if (strcmp(name, "area") == 0) 
		{	
			const char *val1 = get_named_attr("FILEID", atts);
			const char *val2 = get_named_attr("BEGIN", atts);
			if (val1 && val2) 
			{
				typeblock.block = val2;
				typeblock.alto = val1;	
				typeblock.type = currentItem->parent->type;
				currentItem->vectTypeBlock.push_back(typeblock);			
			}
		}
	}
}
void metsParser::XMLendElement(const char *name)
{	
	if(currentstate ==logical)
	{
		if (strcmp(name,"structMap") ==0) 
		{
			// TODO : Delete this code when it's sure that it works without
/*
			Item t;
			t.id = rootItem->id;
			t.children = rootItem->children;
			t.dmdId =rootItem->dmdId;
			t.label =rootItem->label;
			t.parent =rootItem->parent;
			t.type =rootItem->type;
			t.vectTypeBlock =rootItem->vectTypeBlock;
			//dfTemp->set("Item",t);
*/
			currentstate=root;	
		}		
		if (strcmp(name,"div")==0)
		{
			currentItem = currentItem->parent;	
		}
	}	
}

void metsParser::XMLcharacterData(const char *, int )
{
}

Item* metsParser::getItem()
{

	return rootItem;
}

