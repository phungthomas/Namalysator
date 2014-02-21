#include "../common_files/xmltostr.h"

#include <string>
#include <vector>
#include "metsverifier.h"
std::string xml2str(const char *src, int len)
{
	if (len) {
		std::string res;
		while (len) {
			switch (*src) {
				case '"': 
					res += "&quot;";
					break;
				case '<':
					res += "&lt;";
					break;
				case '>':
					res += "&gt;";
					break;
				case '&':
					if ((len >= 4 && 
						((strncmp(src, "&lt;", 4) == 0) ||
						 (strncmp(src, "&gt;", 4) == 0))) ||
					    (len >= 5 && strncmp(src, "&amp;", 5) == 0) ||
						(len >= 6 && strncmp(src, "&quot;", 6) == 0)) {
						res.push_back(*src);
					} else {
						res += "&amp;";
					}
					break;
				default:
					res.push_back(*src);
			}
			--len;
			++src;
		}
		return res;
	} else {
		std::string res;
		while (*src) {
			switch (*src) {
				case '"': 
					res += "&quot;";
					break;
				case '<':
					res += "&lt;";
					break;
				case '>':
					res += "&gt;";
					break;
				case '&':
					if ((strncmp(src, "&lt;", 4) == 0) ||
						(strncmp(src, "&gt;", 4) == 0) ||
					    (strncmp(src, "&amp;", 5) == 0) ||
						(strncmp(src, "&quot;", 6) == 0)) {
						res.push_back(*src);
					} else {
						res += "&amp;";
					}
					break;
				default:
					res.push_back(*src);
			}
			++src;
		}
		return res;
	}
}



std::string xml2stringHeader(const char *name, const char **atts)
{
	std::string xml;
	
	if (strcmp(name,"MODS:mods")==0)
	{
		xml +="<MODS:mods xmlns:MODS=\"http://www.loc.gov/mods/v3\" xmlns:xlink=\"http://www.w3.org/TR/xlink\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.loc.gov/mods/v3 \
 " + linkSchemas +"\\mods-3-0.xsd\">";
	}
	else if (strcmp(name,"mix:mix")==0)
	{
		xml +="<mix:mix xmlns:mix=\"http://www.loc.gov/mix/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.loc.gov/mix/ \
" + linkSchemas +"\\mix.xsd\">";
	}
	else if (strcmp(name,"alto")==0)
	{	
		xml += "<alto xmlns=\"http://schema.ccs-gmbh.com/ALTO\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://schema.ccs-gmbh.com/ALTO " + linkSchemas +"\\alto-1-2.xsd\">";
	}
	return xml;

}

std::string xml2stringBegin(const char *name, const char **atts)
{	
	std::string xml;
	xml += "<";
	xml += name;
	if (atts)
	{
		while (*atts)
		{
			xml += " ";
			xml += *atts;				
			xml += "=\"" + xml2str(*(atts + 1),0) + "\"";			
			atts += 2;
		}
	}
		xml += ">";
	
	return xml;
}

std::string xml2stringEnd(const char *name)
{
	std::string xml;
			
	xml += "</";
	xml += name;
	xml += ">";

	return xml;
}

std::string initializeXmlValidator()
{	
	std::string xml = "<?xml version=\"1.0\"  encoding=\"UTF-8\" ?>";
	return xml;
}

std::string xml2stringData(const char *s, int len)
{
	return std::string(s, len);	
}


