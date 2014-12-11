#ifndef SATEPARSER_H
#define SATEPARSER_H

#include <xercesc/sax2/DefaultHandler.hpp>
#include <string>
#include <stack>

// parsing with state pseudo pattern ( ContentHandler of xerces)
// there is a context class : StateParserContext
// state class : StateParserState
// manager : StateParserCH


class StateParserContext {
public :
	StateParserContext(){};
	virtual ~StateParserContext(){};
};


class StateParserState{
protected :
	StateParserContext* ctx;
public :
	StateParserState();
	virtual ~StateParserState();

	//next state when encounter start tag of type name
	virtual StateParserState* getNext(const char* const name);

	// parsing function
	virtual void characters (const char* const chars, const int len);
    virtual void startElement (const char* const name, const xercesc::Attributes &attrs );
	virtual void endElement (const char* const name);

	// helper
	static char* getAttributeValue (const char* qname, const xercesc::Attributes &attrs); // don't forget to XML String release to avoid memory leak

	// setter of global context : No getter -> non sens
	virtual void setStateParserContext(StateParserContext* _ctx){
		ctx=_ctx;
	}
};

class StateParserCH : public xercesc::DefaultHandler{
protected :
	StateParserContext* ctx;
public:

	StateParserCH(StateParserContext&,StateParserState&);
	virtual ~StateParserCH();

	// adapter from xerces to our internal StateParserState sub interface
	virtual void 	characters (const XMLCh *const chars, const XMLSize_t length);
	virtual void    startElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const xercesc::Attributes &attrs);
	virtual void    endElement (const XMLCh* const uri,const XMLCh* const localname,const XMLCh* const qname);

private:
	
	std::stack<StateParserState*> _stack; // could be a list... but natural like this 
	std::string dataAcc; // accumulation of data

    StateParserState* current; // temporary variable 
};

#endif
