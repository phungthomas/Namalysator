#ifndef STRUCTMAPHYSICALPARSER_H_
#define STRUCTMAPHYSICALPARSER_H_

#include "delegatedparser.h"
#include <stack>

// typedef std::map<std::string,std::vector<std::pair<std::string, std::string> >, article_compare> my_map_type;

//! parse structmap section of Mets and store items in a datafactory
class structmaphysicalparser : public delegatedparser 
{
enum state {	
		stat_struct,		
		state_physical,
		state_block
	};

private :
	std::string id;	
	std::string title;
	state actualState;	
	std::pair<std::string,std::string> pairPile;		
	std::stack <std::string> pile;
	typeBlock typeblock;
	std::vector<Item*> vectItem;

	Item *currentItem;
	Item *rootItem;

	
public:	
	structmaphysicalparser(datafactory *df, XML_Parser orig_expat_parser,const std::string &mets_fname,ErrorHandler *h,std::string validation);
	virtual void startElement(const char *name, const char **atts);
	virtual bool endElement(const char *name);
	virtual void characterData(const char *s, int len);
	virtual void initialize(const char *name,const char **atts);		
};

#endif	//structmaphysicalparser_H_