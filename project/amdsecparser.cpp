#include "amdsecparser.h"
//#include "schema_validatormix.h"
#include "../common_files/utilities.h"
#include "../common_files/xmltostr.h"
#include "metsverifier.h"
#include <boost/algorithm/string.hpp>

// the item of section where the dpi has to be extracted
const char* dpiToExtract = "mix:XphysScanResolution";
const char* sourceDataToExtract = "mix:SourceData";

//!parse the amdsec section with xml validation
amdsecparser::amdsecparser(datafactory *df, XML_Parser orig_expat_parser,const std::string &mets_fname,errorHandler *h)
{	
	actualState = state_amd;
	setDelegatedparameters(df,orig_expat_parser,mets_fname,h);	
	extract_cData = false;	
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
//		lineError = XML_GetCurrentLineNumber(expat_parser);	
	}
	else if (actualState == state_xmlData)
	{
		//xml += 	xml2stringHeader(name,atts);
		actualState = state_mix;
	} 	
	else if (actualState == state_mix)
	{
		//xml += xml2stringBegin(name,atts);	
		if (strcmp(name, dpiToExtract) == 0) {
			extract_cData = true;
		} else if (strcmp(name, sourceDataToExtract) == 0) {
			extract_cData = true;
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
		//xml += xml2stringEnd(name);
		if (strcmp(name, dpiToExtract) == 0) {
			boost::algorithm::trim(cData);
			amdsec.dpi = atoi(cData.c_str());
			extract_cData = false;
		} else if (strcmp(name, sourceDataToExtract) == 0) {
			boost::algorithm::trim(cData);
			amdsec.sourceData = cData;
			extract_cData = false;
		}
	} 	
	else if (actualState == state_amd)
	{		
		if (strcmp(name,"amdSec") == 0)
		{	
			dfTemp->set(amdsec.amdSecId,amdsec);
			/* // No More Validation
			if (schemaValidation =="1")
			{				
				Error error = schema_validatormix(xml,lineError);		    
				if (error.message !="")
				{	
					hError->getMetsError(cat_schema_err,"METS","AMDSEC",error,metsFile);					
				}								
			}
			*/

			return false;		
		}
	}
	return true;		
}

void amdsecparser::characterData(const char *s, int len)
{				
	if (actualState == state_mix )
	{	
		//xml +=	xml2stringData(s,len);
		if (extract_cData == true)
		{
			cData += std::string(s, len);
		}
	}
}


void amdsecparser::initialize(const char *name,const char **atts)
{		
//	xml = initializeXmlValidator();	
	const char *val = get_named_attr("ID", atts);
	if (val!=0)
	{
		amdsec.amdSecId =val;
	}
}
