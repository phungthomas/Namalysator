#include "inventoryparser.h"
#include <string>
#include <iostream>
#include <map>
#include "../common_files/xmltostr.h"








inventoryparser::inventoryparser(SQLLoad* sql):StateParserCH(ctx,_root){	
	ctx.sql = sql;
}

#define CTX (*((inventoryparserContext*)ctx))

class StateParserDocumentState : public StateParserInventoryRootState{
public:
	virtual void startElement (const char* const name, const xercesc::Attributes &atts ){
	   std::vector<std::string> allValue;
       (CTX . sql) -> Store( allValue);
	};
};

StateParserState* StateParserInventoryRootState::getNext(const char* const name){
	
	static std::map<std::string,StateParserState*> map;
	static StateParserState* root=this;

	StateParserState* ret=root;
	
	static struct _onlyOnes {
		_onlyOnes(std::map<std::string,StateParserState*>& map){
			map["document"]=	new StateParserDocumentState();
			map["MeasurementUnit"]=	new StateParserInventoryRootState();
			map["PrintSpace"]=	new StateParserInventoryRootState();
			map["TextBlock"]=
			map["Illustration"]=
			map["ComposedBlock"]=	new StateParserInventoryRootState();
		}
	} onlyOnes (map);

	std::map<std::string,StateParserState*>::iterator it = map.find(name);
	if ( it != map.end()) ret = (*it).second;

	return ret;
}

void StateParserInventoryRootState::startElement (const char* const name, const xercesc::Attributes &attrs ){
	std::cout << "element" << name << std::endl;
}


