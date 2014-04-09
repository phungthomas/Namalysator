#ifndef AMDSECPARSER_H_
#define AMDSECPARSER_H_

#include "delegatedparser.h"

//! Parse amdsec section and store amdid and dpi in the datafactory
class amdsecparser :  public delegatedparser
{
	enum state 
	{
		state_amd,
		state_techMD,
		state_mdWrap,
		state_xmlData,
		state_mix		
	};

	private :
		state actualState;	
		AmdSec amdsec;
		bool extract_cData;
		std::string cData;
	public:	
		amdsecparser(datafactory *df, XML_Parser orig_expat_parser,const std::string &mets_fname,ErrorHandler *h,std::string validation);
		virtual void startElement(const char *name, const char **atts);
		virtual bool endElement(const char *name);
		virtual void characterData(const char *s, int len);
		virtual void initialize(const char *name,const char **atts);			
};

#endif	//AMDSECPARSER_H_