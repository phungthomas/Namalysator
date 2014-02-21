#include "amdsecparser.h"
#include "schema_validatormix.h"
#include "../common_files/utilities.h"
#include "../common_files/xmltostr.h"
#include "metsverifier.h"

// the item of section where the dpi has to be extracted
const char* dpiToextract = "mix:XphysScanResolution";

//!parse the amdsec section with xml validation
amdsecparser::amdsecparser(datafactory *df, XML_Parser orig_expat_parser,const std::string &mets_fname,ErrorHandler *h,std::string validation)
{	
	actualState = state_amd;
	setDelegatedparameters(df,orig_expat_parser,mets_fname,h,validation);	
	inDpi= false;	
}
void amdsecparser::startElement(const char *name, const char **atts)
{		
	if (strcmp(name,"techMD")==0)
	{
		actualState = state_techMD;
	} 
	else if (strcmp(name,"mdWrap")==0)
	{
		actualState = state_mdWrap;
	}
	else if (strcmp(name,"xmlData")==0)
	{
		actualState = state_xmlData;		
		lineError = XML_GetCurrentLineNumber(expat_parser);	
	}
	else if (actualState == state_xmlData)
	{
		xml += 	xml2stringHeader(name,atts);
		actualState = state_mix;
	} 	
	else if (actualState == state_mix)
	{
		xml += 	xml2stringBegin(name,atts);	
		if (strcmp(name, dpiToextract) == 0) { // section to extract to extract dpi
			inDpi = true;
		}	
	} 	
}

bool amdsecparser::endElement(const char *name)
{ 	
	if (strcmp(name,"xmlData")==0)
	{
		actualState = state_mdWrap;
	}
	else if (strcmp(name,"mdWrap")==0)
	{
		actualState = state_techMD;
	}
	else if (strcmp(name,"techMD")==0)
	{
		actualState = state_amd;
	}
	else if (actualState == state_mix)
	{
		xml += xml2stringEnd(name);
		if (strcmp(name, dpiToextract) == 0) {
			amdsec.dpi = atoi(dpistring.c_str());
			inDpi = false;
		}
	} 	
	else if (actualState == state_amd)
	{		
		if (strcmp(name,"amdSec") == 0)
		{	
			dfTemp->set(amdsec.amdSecId,amdsec);
			if (schemaValidation =="1")
			{				
				Error error = schema_validatormix(xml,lineError);		    
				if (error.message !="")
				{	
					hError->getMetsError(cat_schema_err,"METS","AMDSEC",error,metsFile);					
				}								
			}	

			return false;		
		}
	}
	return true;		
}

void amdsecparser::characterData(const char *s, int len)
{				
	if (actualState == state_mix )
	{	
		//if ( (s[0] >= 'a') && (s[0] <= 'z')|| (s[0] >= 'A' && s[0] <= 'Z')||(s[0] >= '0') ||(s[0] == '(') ||(s[0] == ')')||(s[0] =='&')||(s[0] ==';') ||(s[0] =='\"') || (s[0]== ' ' ) )
		//{		
			xml +=	xml2stringData(s,len);
		//}
		if (inDpi == true)
		{
			dpistring += std::string(s, len);
		}
	}
}


void amdsecparser::initialize(const char *name,const char **atts)
{		
	xml = initializeXmlValidator();	
	const char *val = get_named_attr("ID", atts);
	if (val!=0)
	{
		amdsec.amdSecId =val;					
	}
}
