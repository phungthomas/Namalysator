#include "metsparser.h"


metsParser::metsParser(std::string &mets_fname,errorHandler *h,datafactory *df)
{
	hError = h;	
	metsfile = mets_fname;
	currentstate = root;
	current = 0;	
	dfMets = df;
}

void metsParser::XMLstartElement(const char *name, const char **atts)
{		
	if (currentstate == root)
	{
		if (strcmp(name, "mets") == 0) {
			const char *s = get_named_attr("TYPE", atts);
			StringItem papertype;
			papertype.value = (s ? s : "");
			dfMets->set<StringItem>("METS_PAPERTYPE", papertype);
		} else if (strcmp(name,"dmdSec") == 0)
		{			
			current = new dmdsecparser(dfMets, expat_parser,metsfile,hError);	
			currentstate = delegated;	
			current->initialize(name,atts);			
		}
		else if (strcmp(name,"amdSec") == 0)
		{							
			current = new amdsecparser(dfMets, expat_parser,metsfile,hError);	
			currentstate = delegated;	
			current->initialize(name,atts);			
		} 
		else if (strcmp(name,"fileSec") == 0)
		{			
			current = new filegroupparser(dfMets, expat_parser,metsfile,hError);						
			currentstate = delegated;
			current->initialize(name,atts);						
		} 
		else if (strcmp(name,"structMap") == 0)
		{								
			std::string val = get_named_attr("TYPE", atts);
			if (val.find("LOGICAL")!=string::npos)
			{	
				current = new structmapparser(dfMets, expat_parser,metsfile,hError);						
				currentstate = delegated;					
				current->initialize(name,atts);	
			}
		}
	}	
	else
	{			
		current->startElement(name,atts);			
	}
}

void metsParser::XMLendElement(const char *name)
{	
	if (currentstate == root)
	{
	}
	else
	{
		if (current->endElement(name)==false)
		{				
			delete current;
			current =0;
			currentstate =root;			
		}
	}
}

void metsParser::XMLcharacterData(const char *s, int len)
{
	if (currentstate == delegated)
	{			
		current->characterData(s,len);
	}
}
