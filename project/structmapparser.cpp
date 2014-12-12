#include "structmapparser.h"
#include "../common_files/utilities.h"
#include <string>
#include <iostream>
//#include "schema_validatorstruct.h"
#include "xmlsaverstruct.h"
#include "errorhandler.h"

//const std::string article_identifier = "MODSMD_ARTICLE";

//parse the structmap section of the xml file
structmapparser::structmapparser(datafactory *df, XML_Parser orig_expat_parser,const std::string &mets_fname,errorHandler *h)
{		
	setDelegatedparameters(df,orig_expat_parser,mets_fname,h);	
//	lineError = XML_GetCurrentLineNumber(expat_parser);		
	currentItem =0;
	rootItem =0;
}


void structmapparser::startElement(const char *name, const char **atts)
{	
	const char *val1 = get_named_attr("ID", atts);
	const char *val2 = get_named_attr("TYPE", atts);
	const char *val3 = get_named_attr("LABEL", atts);
	const char *val4 = get_named_attr("DMDID", atts);

	/*
	if (val2 !=0)
		if (strcmp(val2,"ADVERTISEMENT_SECTION") ==0 || strcmp(val2,"DEATH_NOTICE_SECTION") ==0)
			xml += "<SECTION>";
		else 
			xml += saveStartElement(name,atts);	
	else 
		xml += saveStartElement(name,atts);		
	*/

	if (strcmp(name,"div")==0)
	{
		//pile.push(val2);		
		if (currentItem ==0)
		{		
			rootItem = new Item;
			rootItem->id = (val1 ? val1 : "");
			rootItem->label = (val3 ? val3 : "");
			rootItem->type = (val2 ? val2 : "");
			rootItem->dmdId = (val4 ? val4 : "");			
			currentItem = rootItem;
		}
		else
		{	
			Item c;				
			c.id = (val1 ? val1 : "");
			c.label = (val3 ? val3 : "");
			c.type = (val2 ? val2 : "");
			c.dmdId = (val4 ? val4 : "");
			c.parent = currentItem; 
			currentItem->children[currentItem->children.size()] = c;
			currentItem = &currentItem->children[currentItem->children.size()-1];			
		}
	}	
	else if (strcmp(name, "area") == 0) 
	{
		//pile.push(name);
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
	else
	{
		//pile.push(name);
	}
}

bool structmapparser::endElement(const char *name)
{ 	
	if (strcmp(name,"structMap") ==0) 
	{		
		Item t;
		t.id = rootItem->id;
		t.children = rootItem->children;
		t.dmdId =rootItem->dmdId;
		t.label =rootItem->label;
		t.parent =rootItem->parent;
		t.type =rootItem->type;
		t.vectTypeBlock =rootItem->vectTypeBlock;
		dfTemp->set("Item",t);
		
		
		if(	actualState == state_logical)
		{	
			/* // no more validation
			if (schemaValidation == "1")
			{
				Error error = g_validator_bnl_newspaper_v1_3.validate(xml,lineError);				
				if (error.message !="")
				{		
					hError->getMetsError(cat_schema_err,"METS","STRUCTMAP",error,metsFile);					
				}				
			}
			*/
			return false; 	
		}
		
	}	
   	
	if (strcmp(name,"div")==0)
	{
		currentItem = currentItem->parent;	
	}	
    
	/*
	if (strcmp(pile.top().c_str(),"ADVERTISEMENT_SECTION") ==0 || strcmp(pile.top().c_str(),"DEATH_NOTICE_SECTION") ==0)
			xml += "</SECTION>";
	else 
		xml += saveEndElement(name,pile.top());		
	*/
	//pile.pop();	

	return true;
}

void structmapparser::characterData(const char *s, int len)
{	
}


void structmapparser::initialize(const char *name,const char **atts)
{		
	//xml= initializeXmlValidator();

	const char *val = get_named_attr("TYPE", atts);
	if (strcmp(val,"LOGICAL")==0)
	{
		actualState = state_logical;
	}
	else
	{
		actualState = state_physical;
	}
}

