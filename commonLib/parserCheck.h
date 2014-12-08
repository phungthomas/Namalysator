#ifndef PARSER_CHECK_H_
#define PARSER_CHECK_H_

#include <string>
#include <memory>

//Xerces stuff

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/framework/XMLGrammarPoolImpl.hpp>

using namespace xercesc;


/// parserCheck : parserFacade -> hide the technology

/**
 * 
 */



class parserCheck {

public :
	parserCheck();
	virtual ~parserCheck();
	
	virtual int addXSD (std::string fileName); //!< append .xsd files to be parsed 
	virtual void lockaddXSD();  //!< need to be call before first parse otherwise xsd list could gow during parsing of xml 
	
	virtual int parse(const char* const     systemId); //!< parse a file : if file not exist : unknown behaviour

	virtual void setErrorHandler(xercesc::ErrorHandler* const handler);
	virtual void setContentHandler(ContentHandler* const handler);

protected: 
	virtual void init();
	virtual void init_feature();

	std::auto_ptr<SAX2XMLReader> parser;	
	XMLGrammarPoolImpl grammarPool;
	
private :
	
};
#endif