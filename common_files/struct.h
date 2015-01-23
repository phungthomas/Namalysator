#ifndef STRUCT_H_
#define STRUCT_H_

#include "../project/datafactory.h"
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

//extern const std::string article_identifier;

//! structure of an dmdsec : a map with  : tag name as key, vector of all the item .
struct dmdsec : public dataitem
{
	static const size_t DATAITEM_ID =1;	
	std::map<std::string,std::string> mapAddStringData;
	
};


struct Inventaire
{
	int id;
	std::string name;
	std::string code;
	std::string input;
	std::string database;
};




//! structure of an error
struct Error
{
	int errorline;
	int errorcolumn;
	std::string message;
	int severity;
};

//! structure of a Type_File 
struct Type_File 
{		
	std::string id;
	std::string checksum;
	std::string checksumtype;
	std::string ref;	
	std::string admid;
	std::string groupId;		
	int seq;
	int size;
	int dpi;
};

//! structure of File_Group 
struct File_Group : public dataitem
{
	static const size_t DATAITEM_ID =2 ;
	std::vector<Type_File> vect;
};

//! structure of an amdsec
struct AmdSec : public dataitem
{
	static const size_t DATAITEM_ID =7;
	std::string amdSecId;
	std::string sourceData;				// mix:ChangeHistory/mix:ImageProcessing/mix:SourceData for cut-outs
	int dpi;
};
//! structure of a block type
struct typeBlock 
{
	std::string type;
	std::string alto;
	std::string block;	
};

//! structure of an Mets
struct Mets : public dataitem
{
	static const size_t DATAITEM_ID =8;
	int idMets;
	int idTestSet;
	int pages;
	std::string path;
	std::string fileName;
	std::string issueNumber;
	std::vector<int> vectIssueNumber;
	std::string title;
	std::vector<std::string> supplements;
	std::string date;
	std::string identifier;
	std::string ausgabe;
	int year;
	std::string papertype; // The type of document as used in the logical structure (e.g. Newspaper, Serial or MonoGraph)

};
/* THIS SEEMS DANGEROUSLY WRONG
struct article_compare
{
	bool operator()(const std::string &a, const std::string &b) const
	{
		if (a.substr(0, article_identifier.length()) == article_identifier &&
			b.substr(0, article_identifier.length()) == article_identifier) {
			int val_a = atoi(a.substr(article_identifier.length()).c_str());
			int val_b = atoi(b.substr(article_identifier.length()).c_str());
			return val_a < val_b;
		} else {
			return false;
		}
	}
};
*/

//! structure of a div type
struct DivType : public dataitem
{
	static const size_t DATAITEM_ID =6;
	std::vector<std::pair<std::string, std::string> > vectDivType;

};

//! structure of an item
struct Item : public dataitem
{
	static const size_t DATAITEM_ID =3;
	int counter;
	std::string id;
	std::string type;
	std::string dmdId;
	std::string label;		
	Item* parent;
	std::map<int,Item> children;
	std::vector<typeBlock> vectTypeBlock;	
};

//! structure of an article
struct Article : public dataitem{
	
	static const size_t DATAITEM_ID =4;
	int id_mets;
	std::string id_article;
	std::string type;
	std::string title;	
	std::string id;	
	std::string div;
	std::vector<typeBlock> vectArticle;
	std::string parentType;
	std::string parentDmdId;	
	int check;	
	int countcaracter;
};

//! structure of a block
struct Block {
	
	long hpos; //x	
	long vpos; //y	
	long width;
	long height;	
	std::string content;
	
	void convert_to_pixel(int dpi = 300) {
		long newx = hpos * dpi / 254;
		long newy = vpos * dpi / 254;
		width = (hpos + width) * dpi / 254 - newx;
		height = (vpos + height) * dpi / 254 - newy;
		vpos = newx;
		hpos = newy;
	}		

	
	void convert_to_mm10(int dpi = 300) {
		long newx = hpos * 254 / dpi;
		long newy = vpos * 254 / dpi;
		width = (hpos + width) * 254 / dpi - newx;
		height = (vpos + height) * 254 / dpi - newy;
		vpos = newx;
		hpos = newy;
	}
};

//! structure of an alto block
struct altoblock : public dataitem {
	
	static const size_t DATAITEM_ID = 5;
	int printSpaceHpos; //x
	int printSpaceVpos;// y
	int printSpaceHeight;
	int printSpaceWidth;
	std::string measurement;
	std::map<std::string,Block> mapalto;
};

//! structure of a id group
struct GroupId : public dataitem {

	enum fileuse
	{
		use_unknown,
		use_images,
		use_pdf,
		use_alto
	};

	static const size_t DATAITEM_ID =9;
	std::string groupId;
	int seq;
	std::map<fileuse,Type_File> map;
};

struct StringItem : public dataitem {
	static const size_t DATAITEM_ID = 10;
	std::string value;
};

struct ErrorTypeMets {
	int id;
	int id_type;
	std::string error;
	std::string details;
	int id_severity;
	//ErrorSeverity severity;
	//ErrorCategory category;
};

#include <common.h>

const static int cat_xml_error=  1;	
const static int cat_schema_err=  2;
const static int cat_wrongFolderName=  3;
const static int cat_missingFile=  4;
const static int cat_sequenceIncorrect=  5;
const static int cat_multipleDmdId=  6;
const static int cat_wrongChecksum= 7 ;
const static int cat_multipleDiv=  8;
const static int cat_unlinkedIdentifier=9;
const static int cat_missingGroupId=  10;	
const static int cat_amdsecID=  11;
const static int cat_multipleBlock=  12;
const static int cat_noIssueDefined=  13;
const static int cat_invalidSupplement=  14;
const static int cat_wrongTitle=  15;					
const static int cat_altoPerPage=  16;	
const static int cat_wrongCoordinates= 17 ;
const static int cat_BlockOutsidePrintspace=  18;
const static int cat_dateMisMatch =  19;
const static int cat_missingIssue=  20;
const static int cat_invalidIssueNumber=  21;
const static int cat_duplicateIssue=  22;	
const static int cat_missingIssueNumber=  23;	
const static int cat_metsFile = 24;
const static int cat_strangePrintspaceNumber = 30;
const static int cat_emptyBlock = 31;
const static int cat_odds = 32;
const static int cat_actualcoverage = 33;
const static int cat_incorrectBlock=  34;
const static int cat_partnumber =  35;
const static int cat_cutoutoriginal =  36;
const static int cat_measurement =  37;


#endif //STRUCT_H_  


