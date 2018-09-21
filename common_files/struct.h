#ifndef STRUCT_H_
#define STRUCT_H_

#include "../project/datafactory.h"
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

//extern const std::string article_identifier,

//! structure of an dmdsec : a map with  : tag name as key, vector of all the item .
struct dmdsec : public dataitem
{
	static const size_t DATAITEM_ID =1;	
	std::map<std::string,std::string> mapAddStringData;
	
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

// TODO: Refactor AmdSec to AmdSecMix and add AmdSecOdrl. Break the code and compile.

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

static const std::string g_group_use_images;
static const std::string g_group_use_pdf;
static const std::string g_group_use_alto;
static const std::string g_group_use_png;

struct GroupID : public dataitem {

	enum fileuse
	{
		use_unknown,
		use_images,
		use_pdf,
		use_alto,
		use_png
	};

	static const size_t DATAITEM_ID =9;
	// Maps the file uses to
	//  a map which maps
	//   the GROUPID to the Type_File inside the File_Group's vect inside the same datafactory
	std::map<fileuse, std::map<std::string, int> > map;
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

#include "common.h"
typedef enum errorTypeEnum {
	cat_xml_error=  1,	
	cat_schema_err=  2,
	cat_wrongFolderName=  3,
	cat_missingFile=  4,
	cat_sequenceIncorrect=  5,
	cat_multipleDmdId=  6,
	cat_wrongChecksum= 7 ,
	cat_multipleDiv=  8,
	cat_unlinkedIdentifier=9,
	cat_missingGroupId=  10,	
	cat_amdsecID=  11,
	cat_multipleBlock=  12,
	cat_noIssueDefined=  13,
	cat_invalidSupplement=  14,
	cat_wrongTitle=  15,					
	cat_altoPerPage=  16,	
	cat_wrongCoordinates= 17 ,
	cat_BlockOutsidePrintspace=  18,
	cat_dateMisMatch =  19,
	cat_missingIssue=  20,
	cat_invalidIssueNumber=  21,
	cat_duplicateIssue=  22,	
	cat_missingIssueNumber=  23,	
	cat_metsFile = 24,
	cat_strangePrintspaceNumber = 30,
	cat_emptyBlock = 31,
	cat_odds = 32,
	cat_actualcoverage = 33,
	cat_incorrectBlock=  34,
	cat_partnumber =  35,
	cat_cutoutoriginal =  36,
	cat_measurement =  37,
	cat_bookinventory = 38,
	cat_inventorynbpages = 39,
	cat_bookinventoryTitle = 50,
	cat_bookinventoryData = 51,
	cat_emptymix = 52,
	cat_nongrpDefine=53,
	cat_nonAccess = 10090
} errorType;


#endif //STRUCT_H_  


