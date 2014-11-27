#include "configparser.h"
#include "../common_files/xmltostr.h"
#include <iostream>

configparser::configparser(Parameters *p)
{	
	currentState = state_root;
	param = p;
}

void configparser::XMLstartElement(const char *name, const char **atts)
{	
	if (strcmp(name,"database")== 0)	
	{
		currentState = state_database;
	}
	else if (strcmp(name,"batchName")== 0)			
	{
		currentState = state_batchName;
	}	
	else if (strcmp(name,"input") == 0)		
	{
		currentState = state_input;
	}
	else if (strcmp(name,"schemaValidation") == 0)		
	{
		currentState = state_schemaValidation ;
	}
	else if (strcmp(name,"checkFile") == 0)		
	{
		currentState = state_checkFile ;
	}
	else if (strcmp(name,"checkSum") == 0)		
	{
		currentState = state_checkSum;
	}
	else if (strcmp(name,"oddsPages") == 0)		
	{
		currentState = state_oddsPages;
	}
		else if (strcmp(name,"checkSum") == 0)		
	{
		currentState = state_checkSum;
	}
	else if(strcmp(name,"unlinkedIdentifier") == 0)		
	{
		currentState = state_unlinkedIdentifier;
	}
	else if (strcmp(name,"identifierMix") == 0)		
	{
		currentState = state_identifierMix;
	}
	else if (strcmp(name,"dateFolderIssue") == 0)		
	{
		currentState = state_dateFolderIssue;
	}
	else if( strcmp(name,"noIssueDefined") == 0)		
	{
		currentState = state_noIssueDefined;
	}
	else if(strcmp(name,"invalidSupplement") == 0)		
	{
		currentState = state_invalidSupplement;
	}
	else if(strcmp(name,"divs") == 0)		
	{
		currentState = state_divs;
	}
	else if(strcmp(name,"altoblockPerPage") == 0)		
	{
		currentState = state_altoblockPerPage;
	}
	else if(strcmp(name,"blockStructure") == 0)		
	{
		currentState = state_blockStructure;
	}		
	else if(strcmp(name,"coveragePercentAlto") == 0)		
	{
		currentState = state_coveragePercentAlto;
	}
	else if (strcmp(name,"multipleBlockUse") == 0)		
	{
		currentState = state_multipleBlockUse;
	}
	else if (strcmp(name,"checkTitle") == 0)		
	{
		currentState = state_checkTitle;
	}
	else if (strcmp(name,"sampling") == 0)		
	{
		currentState = state_sampling;
	}	
	else if (strcmp(name,"dates") == 0)		
	{
		currentState = state_dates;
	}	
	else if (strcmp(name,"issueNumber") == 0)		
	{
		currentState = state_issueNumber;
	}	
}


void configparser::XMLendElement(const char *name)
{		
	currentState = state_root;
}

void configparser::XMLcharacterData(const char *s, int len)
{	
	// TODO : put the assignements into XMLendElement because XMLcharacterData can be called several times
	// if the expat buffer is full (see amdSecParser for correct implementation)
	if (currentState == state_database)
	{
		param->database =	xml2stringData(s,len);	
	}
	else if (currentState == state_batchName)
	{
		param->batchName = xml2stringData(s,len);		
	}
	else if (currentState == state_input)
	{
		param->input = xml2stringData(s,len);		
	}
	else if (currentState == state_schemaValidation)
	{
		param->schemaValidation = xml2stringData(s,len);		
	}		
	else if (currentState == state_checkFile)
	{
		param->checkFile = xml2stringData(s,len);		
	}	
	else if (currentState == state_checkSum)
	{
		param->checkSum = xml2stringData(s,len);		
	}
	else if (currentState == state_divs)
	{
		param->divs = xml2stringData(s,len);		
	}	
	else if (currentState == state_oddsPages)
	{
		param->oddsPages = xml2stringData(s,len);		
	}			
	else if (currentState == state_unlinkedIdentifier)
	{
		param->unlinkedIdentifier = xml2stringData(s,len);		
	}
	else if (currentState == state_identifierMix )
	{
		param->identifierMix = xml2stringData(s,len);		
	}
	else if (currentState == state_altoblockPerPage)
	{
		param->altoblockPerPage = xml2stringData(s,len);		
	}		
	else if (currentState == state_blockStructure)
	{
		param->blockStructure = xml2stringData(s,len);		
	}
	else if (currentState == state_coveragePercentAlto)
	{
		param->coveragePercentAlto = xml2stringData(s,len);		
	}
	else if (currentState == state_multipleBlockUse)
	{
		param->multipleBlockUse = xml2stringData(s,len);		
	}
	else if (currentState == state_invalidSupplement)
	{
		param->invalidSupplement = xml2stringData(s,len);		
	}	
	else if (currentState == state_noIssueDefined)
	{
		param->noIssueDefined = xml2stringData(s,len);		
	}
		else if (currentState == state_checkTitle)
	{
		param->checkTitle = xml2stringData(s,len);		
	}	
		else if (currentState == state_sampling)
	{
		param->sampling = xml2stringData(s,len);		
	}		
	else if (currentState == state_dateFolderIssue)
	{
		param->dateFolderIssue = xml2stringData(s,len);		
	}	
	else if (currentState == state_dates)
	{
		param->dates = xml2stringData(s,len);		
	}		
	else if (currentState == state_issueNumber)
	{
		param->issueNumber = xml2stringData(s,len);		
	}			
}



