#ifndef XMLTOSTR_H_
#define XMLTOSTR_H_
#include <string>

std::string xml2str(const char *src, int len);
std::string xml2stringHeader(const char *name, const char **atts);
std::string xml2stringBegin(const char *name, const char **atts);
std::string xml2stringEnd(const char *name);
std::string xml2stringData(const char *s, int len);
	
#endif // XMLTOSTR_H_