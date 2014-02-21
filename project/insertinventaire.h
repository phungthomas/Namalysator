#ifndef INSERTINVENTAIRE_H_
#define INSERTINVENTAIRE_H_

#include "sqlite3.h"
#include <vector>
#include <map>
#include <string>
#include "../common_files/struct.h"
//! information of the excel sheet
struct info_t
{
	std::string sheetname;
	std::vector<std::string> cells;
	int annexe;
	std::string header;
	
	void clear() {
		sheetname.clear();
		cells.clear();
	}
};


class sqlinventaire
{
private:	
	sqlite3 *db;	
	std::string newspaper;
	std::string databaseName;	
	std::string code;
	int getId(const std::string &table);
	std::map<std::string,std::vector<info_t> > *mapInventaire;
public:	
	sqlinventaire(const std::string &code,const std::string &batchName,const std::string &dataBaseName,std::map<std::string,std::vector<info_t> > *mapInventaire);
	
	bool createTable(const std::string &createTableFile);
	bool openDB();
	void insertInventaire();
	void insertNewspaper();
	void insertSheet();
	void insertExcel(std::vector<info_t> v);
	void insertVolume(std::string volume);

};
#endif // INSERTINVENTAIRE_H_