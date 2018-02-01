#include "inventoryparser.h"
#include <string>
#include <iostream>
#include <map>
#include "../common_files/xmltostr.h"
using namespace xercesc;

inventoryparser::inventoryparser(SQLLoad* sql):StateParserCH(ctx,_root){	
	ctx.sql = sql;
}

#define CTX (*((inventoryparserContext*)ctx))

class StateParserDocumentState : public StateParserInventoryRootState{
public:
	virtual void endElement (const char* const name){
	   CTX.keyValues["languages"]=CTX.languages+",";
	   CTX.languages="";
	   
	   for ( std::map<std::string,std::string>::iterator it = CTX.keyValues.begin();it != CTX.keyValues.end() ; it ++){
		   std::cout << "KEY:" << it->first << " VALUE: " << it->second << std::endl;
	   }

	   std::vector<std::string> allValue;
       
	   (CTX . sql) -> Store( allValue);
	   

	   CTX.keyValues.clear();

	};
	virtual void startElement (const char* const name, const xercesc::Attributes &atts ){	
		std::cout << " Document element:" << name << std::endl;
	}
};


class StateParserParamState : public StateParserInventoryRootState{
	private:
		std::string value;
	public:

		virtual void startElement (const char* const name, const xercesc::Attributes &atts ){	
			value ="";
		}
		virtual void characters (const char* const chars, const int len){
			value+=chars;
		};
		virtual void endElement (const char* const name){
			CTX.keyValues[name]=value;
		}
};

class StateParserLanguageState : public StateParserInventoryRootState{
	private:
		std::string value;
	public:

		virtual void characters (const char* const chars, const int len){
			value+=",";
			value+=chars;
			
		};
		virtual void endElement (const char* const name){
			CTX.languages+=value;
			value="";
		}
};

StateParserState* StateParserInventoryRootState::getNext(const char* const name){
	
	static std::map<std::string,StateParserState*> map;
	static StateParserState* root=this;

	StateParserState* ret=root;
	
	static struct _onlyOnes {
		_onlyOnes(std::map<std::string,StateParserState*>& map){
			map["document"]=	new StateParserDocumentState();
			map["id"]=
			map["type"]=	
			map["paperID"]=
			map["title"]=	
			map["titleCollection"]=
			map["callNumber"]=
			map["subTitle"]=
			map["printer"]=
			map["publisher"]=
			map["day"]=
			map["month"]=
			map["year"]=
			map["pages"]=
			map["yearNumber"]=
			map["odrl"]=
			map["premis"]=
			map["issueNumber"]=
				new StateParserParamState();
			map["language"]=
				new StateParserLanguageState();
			
		}
	} onlyOnes (map);

	std::map<std::string,StateParserState*>::iterator it = map.find(name);
	if ( it != map.end()) ret = (*it).second;

	return ret;
}



