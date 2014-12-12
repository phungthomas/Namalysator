#include "parserCheck.h"

#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/validators/common/Grammar.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <iostream>

using namespace std;

parserCheck::parserCheck():grammarPool(XMLPlatformUtils::fgMemoryManager){
		init();
}

parserCheck::~parserCheck(){
}

int parserCheck::addXSD (string fileName){
		//TODO if it is a xsd
		if (!parser->loadGrammar (fileName.c_str (), Grammar::SchemaGrammarType, true))
        {
          cerr << fileName << ": error: unable to load" << endl;
		  return 1;
        };
		return 0;
}

void parserCheck::lockaddXSD(){
		grammarPool.lockPool();
		init ();
}

void parserCheck::setErrorHandler(ErrorHandler* const handler){
		parser->setErrorHandler(handler);
}

void parserCheck::setContentHandler(ContentHandler* const handler){
		parser->setContentHandler(handler);
}

int parserCheck::parse(const   char* const     systemId) {
		 
		FILE *fp ;
		fopen_s(&fp,systemId, "r");
		if (!fp)
		{			
			std::cerr << "Couldn't open file: " << systemId << std::endl;
			return 1;
		} 

		
		try {
			parser->parse(systemId);
        }
        catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return -1;
        }
		// better to remove this catch and add a real exception mechanism in error handler and the main ( application exception )
		catch (...) {
            
            cerr << "Exception message unhandel: \n" << "\n";
            return -1;
        }
		return 0;
}

 
void parserCheck::init(){
		auto_ptr<SAX2XMLReader> tmpParser (XMLReaderFactory::createXMLReader (XMLPlatformUtils::fgMemoryManager,&grammarPool));
		parser = tmpParser;
		init_feature();
}
	
void parserCheck::init_feature(){
		// Commonly useful configuration.
		//
		parser->setFeature (XMLUni::fgSAX2CoreNameSpaces, true);
	    parser->setFeature (XMLUni::fgSAX2CoreNameSpacePrefixes, true);
	    parser->setFeature (XMLUni::fgSAX2CoreValidation, true);

	    // Enable validation.
	    //
	    parser->setFeature (XMLUni::fgXercesSchema, true);
	    parser->setFeature (XMLUni::fgXercesSchemaFullChecking, true);
	    parser->setFeature (XMLUni::fgXercesValidationErrorAsFatal, true);

	    // Use the loaded grammar during parsing.
	    //
	    parser->setFeature (XMLUni::fgXercesUseCachedGrammarInParse, true);

	    // Don't load schemas from any other source (e.g., from XML document's
	    // xsi:schemaLocation attributes).
	    //
	    parser->setFeature (XMLUni::fgXercesLoadSchema, false);

	    // Xerces-C++ 3.1.0 is the first version with working multi import
	    // support.
	    //
#if _XERCES_VERSION >= 30100
       parser->setFeature (XMLUni::fgXercesHandleMultipleImports, true);
#endif
	
}

