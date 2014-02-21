#ifndef DELEGATEDPARSER_H_
#define DELEGATEDPARSER_H_

#include "datafactory.h"
#include <expat.h>
#include "errorhandler.h"


class delegatedparser 
{
protected:
	XML_Parser expat_parser;	
	std::string xml;
	int lineError;
	std::string metsFile;
	datafactory *dfTemp;
	ErrorHandler *hError;
	std::string schemaValidation;
	
public:
	virtual void startElement(const char *name, const char **atts) = 0;
	virtual bool endElement(const char *name) = 0;
	virtual void characterData(const char *s, int len) = 0;	
	virtual void initialize(const char *name, const char **atts) = 0;	
	virtual ~delegatedparser() {}	
	void setDelegatedparameters(datafactory *df, XML_Parser orig_expat_parser,const std::string &mets_fname,ErrorHandler *h,std::string validation)
	{
	dfTemp = df;
	expat_parser = orig_expat_parser;	
	lineError = XML_GetCurrentLineNumber(expat_parser);		
	metsFile = mets_fname;	
	hError = h;
	schemaValidation = validation;
	}
		
};

#endif //DELEGATEDPARSER_H_