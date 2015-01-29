#include "configparser.h"

#include <memory>
#include <iostream>


#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>

#include "../common_files/xmltostr.h"

using namespace xercesc;
using namespace std;


void    configparser::endElement (const XMLCh* const uri,const XMLCh* const localname,const XMLCh* const qname){
	char* name =XMLString::transcode (qname);
	//cout << "END qname : "<< name << endl ;
	
	XMLString::release(&name);
	if ( save && position.length() > 1 ){
		ctx->addParam(position.substr(1),value);
		save=false;
	}
	value ="";
	currPoss.pop();
	position=currPoss.top();
}

void configparser::startElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const xercesc_3_1::Attributes &attrs){

	char* name =XMLString::transcode (qname);
	std::string tmpName = std::string(name);
	save = true;
	value ="";
	if ( tmpName.compare("config") ) {
		position+="."+tmpName;
	}else{
		position="";
		currPoss.push(position);
	}

	currPoss.push(position);

	XMLString::release(&name);
}

void 	configparser::characters (const XMLCh *const chars, const XMLSize_t length){
	
	char* _chars =XMLString::transcode (chars);

	value+=_chars;
	XMLString::release(&_chars);

};


void configparser::init(){
		std::auto_ptr<SAX2XMLReader> tmpParser (XMLReaderFactory::createXMLReader (XMLPlatformUtils::fgMemoryManager));
		parser = tmpParser;
		parser->setFeature(XMLUni::fgSAX2CoreValidation, false);
		// Commonly useful configuration.
	
		parser->setFeature (XMLUni::fgSAX2CoreNameSpaces, false);
	    parser->setFeature (XMLUni::fgSAX2CoreNameSpacePrefixes, false);
	    parser->setFeature (XMLUni::fgSAX2CoreValidation, false);

	    // Enable validation.
	    //
	    parser->setFeature (XMLUni::fgXercesSchema, false);
	    parser->setFeature (XMLUni::fgXercesSchemaFullChecking, false);
	    parser->setFeature (XMLUni::fgXercesValidationErrorAsFatal, false);

	    // Use the loaded grammar during parsing.
	    //
	    parser->setFeature (XMLUni::fgXercesUseCachedGrammarInParse, false);

	    // Don't load schemas from any other source (e.g., from XML document's
	    // xsi:schemaLocation attributes).
	    //
	    parser->setFeature (XMLUni::fgXercesLoadSchema, false);

	    // Xerces-C++ 3.1.0 is the first version with working multi import
	    // support.
	    //
#if _XERCES_VERSION >= 30100
       parser->setFeature (XMLUni::fgXercesHandleMultipleImports, false);
#endif
	    
        
	    
	    addXSD("xml.xsd");
		setContentHandler(this);

}

configparser::configparser(Parameters *_ctx):ctx(_ctx){
		lockaddXSD();
}

configparser::~configparser(){
}