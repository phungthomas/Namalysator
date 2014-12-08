#include <iostream>
//#include <xercesc/sax/ErrorHandler.hpp>
#include "configparser.h"

/// unitTest the load of a config.xml file 
//

using namespace std;


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

int start (int argc, char** argv){
	Parameters param;
	error_handler eh;
	std::cout << "Hello" << std::endl;
	configparser config(&param);
	
	config.setErrorHandler(&eh);
	if ( config.parse("config.xml") ) {
		return 1;
	};

	
	std::cout << "Database:" <<param.database<< std::endl;
	std::cout << "altoblockPerPage" <<param.altoblockPerPage<< std::endl;
	return 0;
}

int main(int argc, char** argv){

	XMLPlatformUtils::Initialize ();
	
	start (argc,argv);

	XMLPlatformUtils::Terminate ();
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
  //throw new std::exception("Error");
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
