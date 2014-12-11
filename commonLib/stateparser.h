#ifndef SATEPARSER_H
#define SATEPARSER_H

#include <xercesc/sax2/DefaultHandler.hpp>
#include <string>
#include <stack>

// parsing with state pseudo pattern


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

	
	virtual StateParserState* getNext(const char* const name);

	virtual void characters (const char* const chars, const int len);
    virtual void startElement (const char* const name, const xercesc::Attributes &attrs );
	virtual void endElement (const char* const name);

	static char* getAttributeValue (const char* qname, const xercesc::Attributes &attrs); // don't forget to XML String release to avoid memory leak

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

	virtual void 	characters (const XMLCh *const chars, const XMLSize_t length);
	virtual void    startElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const xercesc::Attributes &attrs);
	virtual void    endElement (const XMLCh* const uri,const XMLCh* const localname,const XMLCh* const qname);

private:
	
	std::stack<StateParserState*> _stack;
	std::string dataAcc;

    StateParserState* current;
};

#endif
