#include "StateParser.h"
#include <iostream>
#include <map>
#include <string>
#include <xercesc/sax2/Attributes.hpp>


using namespace std;
using namespace xercesc;


StateParserCH::StateParserCH(StateParserContext& _ctx,StateParserState& hlp):current(&hlp),ctx(&_ctx){
	_stack.push(current);
	//current->setStateParserContext(ctx);
}

StateParserCH::~StateParserCH(){
}

void 	StateParserCH::characters (const XMLCh *const chars, const XMLSize_t length){
	char* _chars =XMLString::transcode (chars);
	dataAcc += std::string (_chars,strlen ( _chars ));
	XMLString::release(&_chars);
}

void    StateParserCH::startElement(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const xercesc::Attributes &attrs){
	dataAcc="";
	char* name =XMLString::transcode (localname);

	current = current -> getNext(name);
    _stack.push(current);
	current->setStateParserContext(ctx);
	current->startElement( name,attrs);

	XMLString::release(&name);
}

void    StateParserCH::endElement (const XMLCh* const uri,const XMLCh* const localname,const XMLCh* const qname){
	
	// only done after accumulation : rmk not very efficient
	current-> characters( dataAcc.c_str(), dataAcc.length());
    dataAcc=""; // convention of non accumulating outside of the most internal tag !!
	
	char* name =XMLString::transcode (localname);

	current->endElement( name);
	_stack.pop();
	current = _stack.top();
	

	XMLString::release(&name);
}





StateParserState::StateParserState(){};
StateParserState::~StateParserState(){};



void StateParserState::characters (const char* const chars, const int len){
	//cout << "StateParserState::characters ->" << chars << endl;
};
void StateParserState::startElement (const char* const name, const Attributes &attrs ){
	//cout << "StateParserState::startElement ->" << name << "<-len:" << attrs.getLength() << endl;
	
	/*
    char* value = getAttributeValue("ID",attrs);
	if (value != NULL ) {
		cout << "VALUE_ID:" << value << endl;
		XMLString::release(&value);
	}



	XMLSize_t len = attrs.getLength();
	for (XMLSize_t i = 0 ; i < len; i++ ){
		
		XMLCh* tmp = (XMLCh*) attrs.getLocalName(i);
		char* _tmp = XMLString::transcode(tmp);
		cout << "idx:"<<i<<endl<<"localname:"<< _tmp << endl;
		XMLString::release(&_tmp);
		
		tmp = (XMLCh*)  attrs.getValue(i);
		_tmp = XMLString::transcode(tmp);
		cout << "Value:" << _tmp << endl;
		XMLString::release(&_tmp);

		tmp = (XMLCh*) attrs.getQName(i);
		_tmp = XMLString::transcode(tmp);
		cout << "QName:" << _tmp << endl;
		XMLString::release(&_tmp);
        


	}*/ 
	 
	

};
void StateParserState::endElement (const char* const name){
	//cout << "StateParserState::endElement ->" << name << endl;
};

StateParserState* StateParserState::getNext(const char* const name){
	cout << "always plaid" << std::endl;
	static std::map<string,StateParserState*> map;
	static struct _onlyOnes {
		_onlyOnes(std::map<string,StateParserState*>& map){
			cout << "this code will be play only ones "<< std::endl;
			map["boss"]=new StateParserState();
		}
	} onlyOnes (map);
	if ( map.find("boss") != map.end()) cout << "FOUND" << endl;
	return this;
}

char* StateParserState::getAttributeValue (const char* qname, const xercesc::Attributes &attrs){
	char* ret=NULL ;
	if ( qname != NULL) {
		XMLCh* _qname = XMLString::transcode(qname);
		const XMLCh* value = attrs.getValue(_qname);

		
		if ( value != NULL ) {
			
			ret = XMLString::transcode(value);
			
			//cout << "VALUE for " << qname << ":" << ret << endl;
		}
		XMLString::release(&_qname);
	}
	return ret;
}