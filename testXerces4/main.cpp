// file      : load-grammar-sax.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : not copyrighted - public domain

// This program uses Xerces-C++ SAX2 parser to load a set of schema files
// and then to validate a set of XML documents against these schemas. To
// build this program you will need Xerces-C++ 3.0.0 or later. For more
// information, see:
//
// http://www.codesynthesis.com/~boris/blog/2010/03/15/validating-external-schemas-xerces-cxx/
//

#include <string>
#include <memory>   // std::auto_ptr
#include <cstddef>  // std::size_t
#include <iostream>

#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XercesVersion.hpp>

#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>

#include <xercesc/validators/common/Grammar.hpp>
#include <xercesc/framework/XMLGrammarPoolImpl.hpp>

#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

#include "parserCheck.h"

using namespace std;
using namespace xercesc;





class myContentHandler : public ContentHandler {

public :
	myContentHandler () {} ;
	~myContentHandler () {} ;

	virtual void 	characters (const XMLCh *const chars, const XMLSize_t length){
		//cExt->characters(chars, length);
		char* _chars =XMLString::transcode (chars);
	    cout << "character : "<< _chars << endl ;
	    XMLString::release(&_chars);
	};
 	
	virtual void 	endDocument (){
		cout << "End document" << endl;
		//cExt->endDocument();
	};
 	 
	virtual void 	endElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname){
		//cExt->endElement(uri,localname,qname);
	};
 	 
	virtual void 	ignorableWhitespace (const XMLCh *const chars, const XMLSize_t length){
		//cExt->ignorableWhitespace(chars,length);
	};
 	
	virtual void 	processingInstruction (const XMLCh *const target, const XMLCh *const data){
		//cExt->processingInstruction(target,data);
	};
 	
	virtual void 	setDocumentLocator (const Locator *const locator){
		//cExt->setDocumentLocator(locator);
	};
 	
	virtual void 	startDocument (){
		cout << "START document" << endl;
		//cExt->startDocument();
	};
 	
 	
	virtual void 	startPrefixMapping (const XMLCh *const prefix, const XMLCh *const uri){
		//cExt->startPrefixMapping(prefix,uri);
	};
 	
	virtual void 	endPrefixMapping (const XMLCh *const prefix){
		//cExt->endPrefixMapping(prefix);
	};
 	
	virtual void 	skippedEntity (const XMLCh *const name){
		//cExt->skippedEntity(name);
	}
 	
    virtual void startElement
    (
        const   XMLCh* const    uri,
        const   XMLCh* const    localname,
        const   XMLCh* const    qname
        , const Attributes&	attrs
    );

private :
	 
};

void myContentHandler::startElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const xercesc_3_1::Attributes &attrs){

	//cExt->startElement(uri,localname,qname,attrs);
	
	char* _uri =XMLString::transcode (uri);
	char* _localname =XMLString::transcode (localname);
	char* _qname =XMLString::transcode (qname);
	
	cout << "URI : " << _uri << endl ;
    cout << "localname : " << _localname << endl ;
	cout << "qname : "<< _qname << endl ;
    
	XMLString::release(&_uri);
	XMLString::release(&_localname);
	XMLString::release(&_qname);
    
	//cout << "AttList : " << attrs ;

}

class error_handler: public ErrorHandler
{
public:
  error_handler () : failed_ (false) {}

  bool
  failed () const { return failed_; }

  enum severity {s_warning, s_error, s_fatal};

  virtual void
  warning (const SAXParseException&);

  virtual void
  error (const SAXParseException&);

  virtual void
  fatalError (const SAXParseException&);

  virtual void
  resetErrors () { failed_ = false; }

  void
  handle (const SAXParseException&, severity);

private:
  bool failed_;
};



//FACADE on SAX2XMLReader
//


int
main (int argc, char* argv[])
{
	int r (0);
	
  if (argc < 2)
  {
    cerr << "usage: " << argv[0] << " [test.xsd ... ] [test.xml ...]" << endl;
    return 1;
  }

  XMLPlatformUtils::Initialize ();

  {
  parserCheck parser; // = new parserCheck(); 

  

  for (int i=1; i < argc; ++i)
  {
	  error_handler eh;
      parser.setErrorHandler (&eh);

      for (; i < argc; ++i)
      {
        string s (argv[i]);
        size_t n (s.size ());

        if (n < 5 || s[n - 4] != '.' || s[n - 3] != 'x' ||
            s[n - 2] != 's' || s[n - 1] != 'd')
          break;

        cerr << "loading " << s << endl;
		r = parser.addXSD(s);

        if (eh.failed ())
        {
          r = 1;
          break;
        }
      }
	  
	  parser.lockaddXSD();
      //error_handler eh;
	  //myContentHandler* tmpch = parser->getContentHandler()  ; 
	  myContentHandler ch;

      parser.setErrorHandler (&eh);
	  parser.setContentHandler(&ch);

      for (; i < argc; ++i)
      {
		  cerr << "parsing " << argv[i] << endl;
		  if ( parser.parse (argv[i])!=0 ){
			  cerr << "file not exist " << argv[i] << endl;
			  r=1;
		  };

          if (eh.failed ())
          {
            r = 1;
        //break;
          }
      }

         break;
      }
		//delete parser;
  }
  XMLPlatformUtils::Terminate ();

  //delete parser;

  return r;
}

void error_handler::
warning (const SAXParseException& e)
{
  handle (e, s_warning);
}

void error_handler::
error (const SAXParseException& e)
{
  // failed_ = true;
  handle (e, s_error);
}

void error_handler::
fatalError (const SAXParseException& e)
{
  // failed_ = true;
  handle (e, s_fatal);
  throw new std::exception("Error");
}

void error_handler::
handle (const SAXParseException& e, severity s)
{
  const XMLCh* xid (e.getPublicId ());

  if (xid == 0)
    xid = e.getSystemId ();

  char* id (XMLString::transcode (xid));
  char* msg (XMLString::transcode (e.getMessage ()));

  cerr << id << ":" << e.getLineNumber () << ":" << e.getColumnNumber ()
       << " " << (s == s_warning ? "warning: " : "error: ") << msg << endl;

  XMLString::release (&id);
  XMLString::release (&msg);
}
