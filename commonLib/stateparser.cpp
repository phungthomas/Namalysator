#include "StateParser.h"
#include <iostream>
#include <map>
#include <string>
#include <xercesc/sax2/Attributes.hpp>

#include <xercesc/util/TransService.hpp>



using namespace std;
using namespace xercesc;


StateParserCH::StateParserCH(StateParserContext& _ctx,StateParserState& hlp):current(&hlp),ctx(&_ctx){
	_stack.push(current);
	//current->setStateParserContext(ctx); // take care the root State has no context 
	                                       // because could be initilize easly 
	                                       // in the constructor inheritance tree
}

StateParserCH::~StateParserCH(){
}

void 	StateParserCH::characters (const XMLCh *const chars, const XMLSize_t length){
	static XMLTransService::Codes failReason;
	static XMLCh* UTF8_ENCODING = XMLString::transcode("UTF-8");;
	static XMLTranscoder* utf8Transcoder = XMLPlatformUtils::fgTransService->makeNewTranscoderFor(UTF8_ENCODING, failReason,16*1024);
    XMLSize_t      charsEaten;
	static char _chars[3000]; // for strange reason when declare like static metsverifier core dump ( however there is not multi threading !!! Strange

	if ( length > 0 ) {
		int col=utf8Transcoder->transcodeTo(chars, length,(XMLByte*)_chars,3000,charsEaten,XMLTranscoder::UnRep_RepChar);
		_chars[col]='\0';
	}else{
		_chars[0]='\0';
	}
	//char* _chars =XMLString::transcode (chars);
	dataAcc += std::string (_chars,strlen(_chars));
	//XMLString::release(&_chars);
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

	current->endElement( name); // play the end of the state

	// come back to the previous state
	_stack.pop();
	current = _stack.top(); 
	

	XMLString::release(&name);
}





StateParserState::StateParserState(){};
StateParserState::~StateParserState(){};



void StateParserState::characters (const char* const chars, const int len){
};
void StateParserState::startElement (const char* const name, const Attributes &attrs ){
};
void StateParserState::endElement (const char* const name){
};

// always overloaded for real work
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

// helper for start element analysor of attributes
char* StateParserState::getAttributeValue (const char* qname, const xercesc::Attributes &attrs){
	static XMLTransService::Codes failReason;
	static XMLCh* UTF8_ENCODING = XMLString::transcode("UTF-8");;
	static XMLTranscoder* utf8Transcoder = XMLPlatformUtils::fgTransService->makeNewTranscoderFor(UTF8_ENCODING, failReason,16*1024);
    XMLSize_t      charsEaten;
	static char _chars[3000]; 

	char* ret=NULL ;


	//std::cerr << failReason << XMLTransService::Ok << qname<< std::endl;

	if ( qname != NULL) {
		XMLCh* _qname = XMLString::transcode(qname);
		const XMLCh* value = attrs.getValue(_qname);
		int len ;
		

		
		if ( value != NULL ) {
			char * tmp = XMLString::transcode(value);
			len = strlen(tmp);
			XMLString::release(&tmp);

			int col = utf8Transcoder->transcodeTo(value, len,(XMLByte*)_chars,3000,charsEaten,XMLTranscoder::UnRep_RepChar);
			_chars[col]='\0';
			
			
			ret = strdup(_chars); // don't forgot to free
			//ret = XMLString::transcode(value); // possible memory leak : ret must be XMLString::release(ret)
			//std::cerr << "VAL1:" << _chars << std::endl << "VAL2:" << ret <<std::endl << std::endl;
		}
		XMLString::release(&_qname);
	}
	return ret;
}