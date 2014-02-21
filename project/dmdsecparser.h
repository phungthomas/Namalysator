#ifndef DMDSECPARSER_H_
#define DMDSECPARSER_H_

#include "delegatedparser.h"

typedef std::map<std::string,std::vector<std::string>> my_map_DmdSec;

//! parse dmdsec section of Mets and store items in a datafactory
class dmdsecparser: public delegatedparser
{		
	enum stateDmd 
	{
		type_root,
		type_mdWrap,
		type_xmlData,
		type_mods,
	}; 
	private :		
		std::string idItem;		
		stateDmd type;					
		std::vector<std::string> vectormap;
		std::string idkeymap;
		dmdsec dmdSecStruct;		
		std::string addStringData;
	public:	
		dmdsecparser(datafactory *df, XML_Parser orig_expat_parser,const std::string &mets_fname,ErrorHandler *h,std::string validation);
		virtual void startElement(const char *name, const char **atts);
		virtual bool endElement(const char *name);
		virtual void characterData(const char *s, int len);
		virtual void initialize(const char *name,const char **atts);			
};

#endif	//DMDSECPARSER_H_