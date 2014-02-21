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

//! main parser for the mets file
class metsParser : public xmlparser_with_stack<metsParser>
{	
	enum state	
	{
		root,
		delegated
	};
	
private:	
	state currentstate;
	delegatedparser *current;
	datafactory *dfMets;	
	std::string metsfile;	
	ErrorHandler *hError;
	std::string xmlvalidation;
public:
	metsParser(std::string &mets_fname,ErrorHandler *h,datafactory *df,std::string validation);
	virtual void XMLstartElement(const char *name, const char **atts);
	virtual void XMLendElement(const char *name);
	virtual void XMLcharacterData(const char *s, int len);		
};

#endif // METSPARSER_H_
