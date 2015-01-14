#ifndef SQLLOADINVENTORY_H_
#define SQLLOADINVENTORY_H_

#include "dbconnection.h"

class SQLLoadInventory : public DbConnection {
public :
	SQLLoadInventory(std::string _dbfileName, std::string _sqlschemafileName);
	~SQLLoadInventory();
};

#endif