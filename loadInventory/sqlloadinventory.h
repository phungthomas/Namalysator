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
private :

};

class SQLLoadInventory : public DbConnection {
public :
	SQLLoadInventory(std::string _dbfileName, std::string _sqlschemafileName);
	~SQLLoadInventory();
	SQLLoad& getSQLLoad(){return sqlLoad; };
private:
	SQLLoad sqlLoad;
};

#endif