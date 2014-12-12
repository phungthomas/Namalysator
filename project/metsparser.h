#ifndef METSPARSER_H_
#define METSPARSER_H_

#include "../common_files/xmlparser.h"
#include "dmdsecparser.h"
#include "amdsecparser.h"
#include "filegroupparser.h"
#include "altoparser.h"
#include "structmapparser.h"
#include "structmaphysicalparser.h"
#include <iostream>
#include <vector>
#include "datafactory.h"
#include "metsparser.h"
#include "errorhandler.h"
#include "stateparser.h"


class metsparserContext : public StateParserContext{

public :
	enum state	
	{
		root,
		delegated
	};
	state currentstate;
	delegatedparser *current;
	datafactory *dfMets;	
	std::string metsfile;	
	errorHandler *hError;

	// need by structMap
	Item *currentItem;
	Item *rootItem;
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
};

#endif // METSPARSER_H_
