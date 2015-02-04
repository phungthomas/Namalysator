#ifndef PARAMETERMETS_H__
#define PARAMETERMETS_H__

#include <common.h>
#include <parserCheck.h>
#include <map>

//*** @class ParameterMETS :specialised class to handle dynamically load of xsd 

class ParameterMETS : public Parameters {
public :

	static const std::string XSDprefix;

	ParameterMETS();
	virtual ~ParameterMETS();

	virtual void addParam(std::string Key,std::string Val); 

	parserCheck* getParser(std::string Key);

private :

	void typeDefine (std::string type);
	void addXSD (std::string filename);
	void lockXSD (std::string filename);


	parserCheck* currentParserCheck; // facilities : tempory transit
	std::map<std::string,parserCheck*> parserCheckSet;
};

#endif