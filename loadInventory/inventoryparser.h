#ifndef INVENTORYPARSER_H_
#define INVENTORYPARSER_H_

#include "stateparser.h"
#include "sqlloadinventory.h"
#include <map>


class inventoryparserContext : public StateParserContext{
	
public :

	SQLLoad* sql;
	std::string file;
	std::string languages;
	std::map<std::string,std::string> keyValues;
	
};

class StateParserInventoryRootState:public StateParserState{
public:
	StateParserInventoryRootState(){};
	virtual ~StateParserInventoryRootState(){};

	virtual StateParserState* getNext(const char* const name);
};

//! parse Inventory files and in map of document
class inventoryparser: public StateParserCH{
		
private :
	inventoryparserContext ctx;
	StateParserInventoryRootState _root;

public:	
	inventoryparser(SQLLoad* sql);
};

#endif	INVENTORYPARSER_H_