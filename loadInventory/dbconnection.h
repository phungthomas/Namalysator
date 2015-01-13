#ifndef DB_CONNECTION_H_
#define DB_CONNECTION_H_

#include <string>
#include "sqlite3.h"

#define VERSIONHARDCODED "15.1"

class DbConnection {
public:
	DbConnection (std::string _dbfileName, std::string _sqlschemafileName);
	~DbConnection ();

	void openDB();
	void closeDB();

	bool isConnected();

private:

	bool readVersion();
	void createSchema();

	sqlite3 *db;
	bool connected;
	std::string dbfileName;
	std::string sqlschemafileName;
	std::string version;
};

class DbConnectionException {
public :
	DbConnectionException(std::string msg);
	~DbConnectionException();

	void print ();

private :
	std::string message;
};

#endif
