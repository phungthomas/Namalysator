#include <iostream>
#include <string>
#include "xmlsaverstruct.h"
#include "../common_files/utilities.h"
#include "../common_files/xmltostr.h"
#include "metsverifier.h"
bool endline = false;
std::string saveStartElement(const char *name, const char **atts)
{
	std::string xml;
	if (endline==false)
		xml += "\n";
	else 
		endline =false;
		
	if (strcmp("div",name)==0)
	{		
		if (strcmp(get_named_attr("TYPE", atts),"Newspaper")==0)
		{
			xml += "<Newspaper xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation= \"" + linkSchemas + "C:\\Data\\schemas\\bnl-newspaper_v1.1.xsd\">";
		}
		else
		{
			xml += "<";
			xml+= get_named_attr("TYPE",atts)	;
				xml += ">";	
		}
	}
	else
	{
		xml += "<";
		xml += name;		
		if (atts) {	
			while (*atts) 
			{			
				xml += " ";
				xml += *atts;				
				xml += "=\"" + xml2str(*(atts + 1),0) + "\"";		
				atts += 2;
			}
			xml += ">";
		}
	}	
	return xml; 
}

std::string saveEndElement(const char *name,std::string top)
{
	std::string xml;
	xml += "</";
	xml += top;
	xml += ">\n";
endline =true;
return xml;
}


std::string saveCharacterData(const char *s, int len)
{
	return std::string(s, len);	
}

