#ifndef COMMON_H__
#define COMMON_H__
struct Parameters
{
	std::string input;
	std::string batchName;
	std::string database;
	std::string inventoryFile; //+ Name of the inventory .csv File
	// std::string schemaValidation; No more validation like must be done by the parser itself
	std::string dateFolderIssue;
	std::string dates;
	std::string checkFile;
	std::string checkSum;
	std::string divs;
	std::string unlinkedIdentifier;
	std::string identifierMix;	
	std::string altoblockPerPage;
	std::string blockStructure;
	std::string coveragePercentAlto;	
	std::string multipleBlockUse;
	std::string invalidSupplement;
	std::string noIssueDefined;	
	std::string checkTitle;
	std::string oddsPages;
	std::string sampling;
	std::string issueNumber;
	std::string measurementSTD;
};
#endif