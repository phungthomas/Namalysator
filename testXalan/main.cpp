
#include <configparser.h>
#include <iostream>

#include <parserCheck.h>
#include "transform.h"

#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

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

  std::cerr << id << ":" << e.getLineNumber () << ":" << e.getColumnNumber ()
	  << " " << (s == s_warning ? "warning: " : "error: ") << msg << std::endl;

  XMLString::release (&id);
  XMLString::release (&msg);
}


int start(){
	parserCheck parserCall;
	std :: cout << "1:" << std::endl;

	parserCall.addXSD("mets.xsd");
	parserCall.addXSD("mods-3-2.xsd");
	parserCall.addXSD("mods-3-3.xsd");
	parserCall.addXSD("xlink.xsd");
	std :: cout << "2:" << std::endl;
	parserCall.lockaddXSD();
	std :: cout << "3:" << std::endl;
	transformParser transformCH;
	transformCH.getContext().openFile("YETANOTHERTEST.xml");
	error_handler eh;
	std :: cout << "4:" << std::endl;

	parserCall.setContentHandler(&transformCH);
	parserCall.setErrorHandler(&eh);

	std :: cout << "5:" << std::endl;

	if ( parserCall.parse( "Hello.xml")!= 0){
			std::cerr << "STOP immediately --> see trace in DB" << std::endl;
			return -1;
		};

	transformCH.getContext().closeFile();

	std::cerr << "FIRST END" << std::endl;

	parserCheck parserCall2;

	
	//parserCall2.addXSD("XMLSchema.xsd");
	parserCall2.addXSD("bnl-monograph_v1.0.xsd");

	parserCall2.lockaddXSD();
	parserCall2.setErrorHandler(&eh);

	
	if ( parserCall2.parse( "YETANOTHERTEST.xml")!= 0){
			std::cerr << "STOP immediately --> see TOTO" << std::endl;
			return -1;
		};





	return 0;
}


int main () {

	std :: cout << "Hello World" << std::endl;

	XMLPlatformUtils::Initialize ();
	
	start ();

	XMLPlatformUtils::Terminate ();
}
