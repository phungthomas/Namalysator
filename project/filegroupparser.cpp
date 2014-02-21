#include "filegroupparser.h"
#include "errorhandler.h"
#include "../common_files/utilities.h"
#include "../common_files/xmltostr.h"
#include <string>
#include <iostream>

//parse the Filegroup section of the xml
filegroupparser::filegroupparser(datafactory *df, XML_Parser orig_expat_parser,const std::string &mets_fname,ErrorHandler *h,std::string validation)
{
	actualState = state_fileSec;
	setDelegatedparameters(df,orig_expat_parser,mets_fname,h,validation);	
}

void filegroupparser::startElement(const char *name, const char **atts)
{
	xml += 	xml2stringBegin(name,atts);
	if (actualState == state_fileSec)
	{	
		if ( strcmp(name,"fileGrp") == 0)
		{	
			const char *val = get_named_attr("ID", atts);	
			idGroup = "";
			if (val != 0) 
			{
				idGroup = val;						
			}	

			actualState = state_fileGrp;			
		}
	}
	else if (actualState = state_fileGrp)
	{
		if ( strcmp(name,"file") == 0)
		{	
			const char *val = get_named_attr("ID", atts);
			f.id ="";
			if (val != 0) 
			{				
				f.id = val;					
			}			
			const char *val2 = get_named_attr("GROUPID", atts);		  
			f.groupId ="";
			if (val2 != 0) 
			{				
				f.groupId = val2;		
			}
			else
			{
				hError->getError(cat_missingGroupId,"METS","FILESEC","GROUPID missing",metsFile,get_named_attr("CHECKSUM", atts));
			}
			const char *val3 = get_named_attr("CHECKSUM", atts);			
			f.checksum ="";
			if (val3 != 0) 
			{				
				f.checksum = val3;					
			}
			const char *val4 = get_named_attr("SIZE", atts);			
			f.size =0;
			if (val4 != 0) 
			{				
				f.size = atoi(val4);					
			}
			const char *val5 = get_named_attr("ADMID", atts);	
			f.admid ="";
			if (val5 != 0) 
			{				
				f.admid = val5;					
			}			
			const char *val6 = get_named_attr("SEQ", atts);	
			f.seq =0;
			if (val6 != 0) 
			{				
				f.seq = atoi(val6);					
			}

			actualState = state_file;
		}
		else if (actualState = state_file)
		{
			if (strcmp(name,"FLocat")==0)
			{
				const char	*val5 = get_named_attr("xlink:href", atts);
				f.ref ="";
				if (val5 != 0) 
				{
					std::string my_id = val5;
					//remove file://./
					my_id = my_id.substr(8,my_id.size());
					f.ref = my_id;				
					file_group.vect.push_back(f);					
					actualState = state_locat;		
				}
			}		
		}	
	}
}

bool filegroupparser::endElement(const char *name)
{ 	
	xml += xml2stringEnd(name);
	if (actualState == state_locat)
	{
		if (strcmp("FLocat", name) ==0)
		{
			actualState =state_file;		
		}
	}
	else if (actualState == state_file)
	{	
		if (strcmp("file", name) ==0)
		{
			actualState =state_fileGrp;		
		}
	}
	else if (actualState ==state_fileGrp)
	{	
		if (strcmp("fileGrp", name) ==0)
		{
			dfTemp->set(idGroup,file_group);
			file_group.vect.clear(); 
			actualState =state_fileSec;		
		}
	}
	else if (actualState ==state_fileSec)
	{	
		if (strcmp("fileSec", name) ==0)
		{			
			return false;
		}
	}
	return true;
}

void filegroupparser::characterData(const char *s, int len)
{
}

void filegroupparser::initialize(const char *name,const char **atts)
{	
	xml = initializeXmlValidator();
}
