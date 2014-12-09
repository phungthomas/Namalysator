#ifndef FILEGROUP_H_
#define FILEGROUP_H_

#include "delegatedparser.h"

//! Parse filegroup section of Mets and store items in a datafactory
class filegroupparser : public delegatedparser
{
	enum state
	{
		state_fileSec,
		state_fileGrp,
		state_file,
		state_locat
	};
			
private :
	state actualState;
	std::string idGroup;	
	Type_File f;
	File_Group file_group;
	
public:	
	filegroupparser(datafactory *df, XML_Parser orig_expat_parser,const std::string &mets_fname,errorHandler *h);
	virtual void startElement(const char *name, const char **atts);
	virtual bool endElement(const char *name);
	virtual void characterData(const char *s, int len);
	virtual void initialize(const char *name,const char **atts);		
	Type_File& getElement(int i);
};

#endif	//FILEGROUP_H_