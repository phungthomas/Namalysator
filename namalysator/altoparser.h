#ifndef ALTOPARSER_H_
#define ALTOPARSER_H_

#include "../common_files/xmlparser.h"
#include "altoparser.h"
#include <map>
#include "structgui.h"
	 
extern const std::string block_identifier;

//! compare the articles 
struct block_compare
{
	bool operator()(const std::string &a, const std::string &b) const
	{
		if (a.substr(0, block_identifier.length()) == block_identifier &&
			b.substr(0, block_identifier.length()) == block_identifier) {
			int val_a = atoi(a.substr(block_identifier.length()).c_str());
			int val_b = atoi(b.substr(block_identifier.length()).c_str());
			return val_a < val_b;
		} else 
		{
			return false;
		}
	}
};

typedef std::map<std::string,std::string, block_compare> my_map_alto;
//! Parse the alto file
class altoparser: public xmlparser_with_stack<altoparser>
{
	enum state 
	{	
		state_header,
		state_alto,
		state_block		
	};
		
private :
	state currentstate;
	std::string content;
	std::string idBlock;	
	my_map_alto map;	
	std::string xml;
	std::string altoFile;
	altoblock altoBlock;	
	bool measurement_unit ;
	bool is_mm10;
	bool convert_to_pixels;
	int  dpi;
	std::set<std::string> to_extract;
	
protected : 
	std::string alto;
	Block block,blockPrintspace;	
	long printSpaceHpos;
	long printSpaceVpos;
	long printSpaceHeight;
	long printSpaceWidth;
	long hpos;
	long vpos;
	long height;
	long width;
	//std::map<std::string,altoblock> *mapAlto;

public:	
	altoparser(std::string &fname,LinkedFiles lf,int dpi);
	virtual void XMLstartElement(const char *name, const char **atts);
	virtual void XMLendElement(const char *name);
	virtual void XMLcharacterData(const char *s, int len);	
	virtual void getElement(const char *name, const char **atts);
	altoblock getAltoBlock();
};

#endif	//ALTOPARSER_H_