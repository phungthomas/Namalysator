#ifndef SQLLOADINVENTORY_H_
#define SQLLOADINVENTORY_H_

#include <vector>
#include "dbconnection.h"


// manage the statement
//
class SQLLoad {
public : 
	SQLLoad();
	~SQLLoad();
	void Start();
	void Store(std::vector<std::string> allValue);
	sqlite3 *db;
private :
	std::string sql;
	const char *zErrMsg ;
	sqlite3_stmt *pStmt ;

};

class SQLLoadInventory : public DbConnection {
public :
	SQLLoadInventory(std::string _dbfileName, std::string _sqlschemafileName);
	~SQLLoadInventory();
	SQLLoad& getSQLLoad();
private:
	SQLLoad sqlLoad;
};

#endif