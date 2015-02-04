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

	virtual void addParam(std::string Key,std::string Val); //+ overloaded call parent function if not defining a xsd manager
	parserCheck* getParser(std::string Type); //+ give the parser for the type

private :

	void typeDefine (std::string type);
	void addXSD (std::string filename);
	void lockXSD (std::string filename);


	parserCheck* currentParserCheck; // facilities : tempory transit
	std::map<std::string,parserCheck*> parserCheckSet;
};

#endif