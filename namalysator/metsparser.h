#ifndef METSPARSER_H_
#define METSPARSER_H_

#include "../common_files/xmlparser.h"
#include <iostream>
#include <vector>
#include <stack>
#include "structgui.h"
//![Test commentaire pour metsparser]
class metsParser : public xmlparser_with_stack<metsParser>
{	
	enum state	
	{
		root,	
		in,	
		logical
	};
	
private:			
	std::string xml;
	int counter;
	state currentstate;
	std::string metsfile;
	std::string batchName;
	typeBlock typeblock;

std::stack <std::string> pile;
	Item *currentItem;
	Item *rootItem;
public:
	metsParser(std::string &mets_fname,Item *itemtree);
	virtual void XMLstartElement(const char *name, const char **atts);
	virtual void XMLendElement(const char *name);
	virtual void XMLcharacterData(const char *s, int len);		
	Item* getItem();
	
};

#endif // METSPARSER_H_
