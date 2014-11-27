#include "dmdsecparser.h"
#include "../common_files/utilities.h"
#include "schema_validatordmdsec.h"
#include "../common_files/xmltostr.h"
#include <iostream>
#include <boost/algorithm/string.hpp>

dmdsecparser::dmdsecparser(datafactory *df, XML_Parser orig_expat_parser,const std::string &mets_fname,ErrorHandler *h,std::string validation)
{		
	setDelegatedparameters(df,orig_expat_parser,mets_fname,h,validation);	
	type = type_root;	
	addStringData.clear();
}

void dmdsecparser::startElement(const char *name, const char **atts)
{		
	if (type == type_mods)
	{	
		xml += xml2stringBegin(name,atts);
	}
	else if (strcmp(name,"mdWrap")==0)
	{
		type = type_mdWrap;
	}
	else if (strcmp(name,"xmlData")==0)
	{
		lineError = XML_GetCurrentLineNumber(expat_parser);	
		type = type_xmlData;
	}
	else if (type == type_xmlData)
	{
		xml += 	xml2stringHeader(name,atts); 
		type = type_mods;
	} 
}

bool dmdsecparser::endElement(const char *name)
{ 	
	if (strcmp(name,"xmlData")==0)
	{
		type = type_mdWrap;
	}
	else if (strcmp(name,"mdWrap")==0)
	{
		type = type_root;
	}
	else if (type == type_mods)
	{
		xml += xml2stringEnd(name);

		idkeymap = name;
		// trim whitespace, tabs, newlines from character Data
		boost::algorithm::trim(addStringData);

		if( dmdSecStruct.mapAddStringData.find(idkeymap) == dmdSecStruct.mapAddStringData.end())
		{
			boost::algorithm::trim(addStringData);
			dmdSecStruct.mapAddStringData[idkeymap] = addStringData;
			addStringData.clear();
		}
		else
		{			
			dmdSecStruct.mapAddStringData[idkeymap].append(" " +addStringData);				
			addStringData.clear();
		}		

		if (strcmp(name,"MODS:mods")==0)
		{
			type = type_xmlData;
		}
	}	
			 
	if (strcmp(name,"dmdSec") == 0)
	{	
	
		dfTemp->set(idItem,dmdSecStruct);			
		
		if (schemaValidation =="1")
		{	
			Error error = schema_validatordmdsec(xml,lineError);		    
			if (error.message !="")
			{		
				hError->getMetsError(cat_schema_err,"METS","DMDSEC",error,metsFile);			
			}			
		}
		return false;
	}	
	return true;		
}

void dmdsecparser::characterData(const char *s, int len)
{	
	if (type == type_mods)
	{			
		xml +=	xml2str(s,len);		
		//if ( (s[0] >= 'a') && (s[0] <= 'z')|| (s[0] >= 'A' && s[0] <= 'Z')||(s[0] >= '0') ||(s[0] == '(') ||(s[0] == ')')||(s[0] =='&')||(s[0] ==';') ||(s[0] =='\"') || (s[0]== ' ' ) )
		//{		
			addStringData += xml2str(s,len);		
		//}		
	}
 }

void dmdsecparser::initialize(const char *name,const char **atts)
{			
	xml = initializeXmlValidator();
	const char *val = get_named_attr("ID", atts);
	if (val != 0) 
	{		
		idItem = val;						
	}		 
}
