#include "../common_files/xmltostr.h"

#include <string>
#include <vector>
//#include "metsverifier.h"
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



std::string xml2stringData(const char *s, int len)
{
	return std::string(s, len);	
}


