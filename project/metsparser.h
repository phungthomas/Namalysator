#ifndef METSPARSER_H_
#define METSPARSER_H_



#include <iostream>
#include <vector>
#include <map>
#include "datafactory.h"
#include "errorhandler.h"
#include "stateparser.h"
#include "inventory.h"


class metsparserContext : public StateParserContext{

public :
	metsparserContext():flagMix(false){};
	datafactory *dfMets;	
	std::string metsfile;	
	errorHandler *hError;

	// need by structMap
	Item *currentItem;
	Item rootItemLOGICAL;
	Item rootItemPHYSICAL; // non use today but fill by 
	Item* rootItem;
	typeBlock typeblock; // probably could go outside of the context

	// need by filegroup	
	std::string idGroup;	
	Type_File f;
	File_Group file_group;

	// dmd
	std::string idItem;
	std::string addStringData;
	dmdsec dmdSecStruct;

	// amdsec
	AmdSec amdsec;

	inventoryMappingActif inventory;

	//testmix;
	bool flagMix ; // if true test mix:mix ( ScannerManufacturer )
	std::map<std::string,std::string> MixContainer;

	//DIV structure;
	//std::map<std::string,std::string> divID;
	//std::vector<std::string> divSuite;
};

class StateParserMetsRootState:public StateParserState{
public:
	StateParserMetsRootState(){};
	virtual ~StateParserMetsRootState(){};

	virtual StateParserState* getNext(const char* const name);
};

//! main parser for the mets file
class metsParser : public StateParserCH
{	
private:
	StateParserMetsRootState _root;
	metsparserContext ctx;
public:
	metsParser(std::string &mets_fname,errorHandler *h,datafactory *df);
	inline metsparserContext& getContext(){return ctx;};
};

#endif // METSPARSER_H_
