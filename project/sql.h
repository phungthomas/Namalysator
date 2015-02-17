#ifndef SQL_H_
#define SQL_H_

#include "sqlite3.h"
#include "datafactory.h"
#include "../common_files/struct.h"
#include "inventory.h"
//#include "metsparser.h"

class metsparserContext;
//! sql queries to the database
class database
{
private:	
	sqlite3 *db;
	typedef std::map<std::string,std::vector<std::string>> my_map_type;
	std::string batchName;
	int idTestset;
	std::string stringIdTestSet;
	std::string databaseName;	
	std::string logFilePath;

	void deletePARAMTESTSET();
	
public:
	//! constructor with batchName and dataBaseName as parameter
	database(const std::string &batchName,const std::string &dataBaseName,const std::string &logFile);
	//! open database
	bool openDB();
	void closeDB();
	void startTransaction();
	void endTransaction();

	void dberror(std::string);
	//! \ set id of the current Testset	
	void setIdTestSet();		
	//! insert all data of the datafactory in the database
	//! \param df as a datafactory
	bool insertALLData(datafactory *df,metsparserContext&,int );
	
	//! create tables of the database
	//! \param createTableFile path of the database path
	//! return true if the database was created successfully, otherwise FALSE
	bool createTable(const std::string &filePath);
	//! insert LinkedFiles into the database
	//! \param datafactory with File_Group as type
	void insertLinkedFiles(int,datafactory *df);
	
	//! update Mets details	
	void updateMets(int,datafactory *df);
	//!insert Article into Database
	void insertArticle(int,datafactory_set<Article> dfarticle,int);
	//! insert Mets error get from parser
	void insertMetsError(int category,const std::string &relatedType,const std::string &filePart,const Error &e);
	
	bool insertTestSet(const std::string &batchName,const std::string & subBatch,const std::string &date);
	void insertMets(const std::string &batchName,const std::string &path,const std::string &fileName);	
	int select_idMets();	
	std::vector<int> getAllYears();
	std::vector<std::pair<int,Mets>> vMetsYear(int year);
	
	//for GUI
	int getIdTestSet(const std::string &batchName);
	
	std::vector<std::string> guiVectSelectDateTestset(std::string batch);
	void insertDateError(int category,std::string dateBegin,std::string dateEnd,std::string issues,std::string comment);
	void insertRandomTitle();
	//! function for samples of structures
	void insertRandomMets(int number,int totalMets);
	void insertParameterVerifiers(Parameters *param);
	
	ErrorTypeMets getErrorTypeWithId(int id);
	void insertMetsErrorWithId(int category,const std::string &relatedType,const std::string &filePart,const Error &e,std::string id);
	
	//! insert error message into log
	void insertLog(std::string message);

	bool FillSupplements(int idMets, std::vector<string> &supplements);
	bool getInventory(std::string _sysnum, inventory&);
	bool InventoryChecked(std::string _sysnum);
	bool insertMetsBook(int id_mets, std::string _sysnum); 
};
#endif // SQL_H_