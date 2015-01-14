#include "dbconnection.h"
#include <iostream>
#include <fstream>
//#include <sstream>
#include <vector>

DbConnection::DbConnection (std::string _dbfileName, std::string _sqlschemafileName):
		dbfileName(_dbfileName),
		sqlschemafileName(_sqlschemafileName),
		connected(false){
}

DbConnection::~DbConnection (){
}

void DbConnection::openDB(){
	// see if file exist before 
	//
	bool fileNotExist = true; // not yet tested
	int rc = sqlite3_open(dbfileName.c_str(), &db);
	
	if( rc )
	{
		std::cerr << "Can not open database: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		db = 0;
		connected = false;
		throw DbConnectionException ( "Problem with db file:"+dbfileName); 
	};

	// if version not define means that schema of creation has never been plaid 
	// but must take care that for old database there is no metadata table and so version is not known
	// in that case, having an idea if the file exist before could be use too avoid to create and recreate
	// TODO : analyse the logic seems only necessary for namalysator and never else where
	//
	if (!readVersion()) {
		if ( fileNotExist ) {
			createSchema();
		} else {
			throw DbConnectionException ( "Existing db without good version" + sqlschemafileName );
		}
		if (!readVersion()) throw DbConnectionException ( "Unable to get version: create sql file " + sqlschemafileName ); 
	};
	
	connected = true;
}

void DbConnection::closeDB(){
	sqlite3_close(db);
	db = 0;
	connected = false;
}

void DbConnection::startTransaction(){
	char *sErrMsg=0;
	
	// Use a transaction to speed things up
	int rc=sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &sErrMsg);
		if ( rc != SQLITE_OK ){
		std::string error (sErrMsg);
		std::cerr << "ERROR BEGIN TRANSATCTION" << error << std::endl;
		sqlite3_free(sErrMsg);
	}

}
void DbConnection::endTransaction(){
	char *sErrMsg=0;
	
	// Use a transaction to speed things up
	int rc=sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &sErrMsg);
	if ( rc != SQLITE_OK ){
		std::string error (sErrMsg);
		std::cerr << "ERROR END TRANSATCTION" << error << std::endl;
		sqlite3_free(sErrMsg);
	}

}

bool DbConnection::isConnected(){
	return connected;
}

// init version field : if impossible means that must be plaid create file
//
bool DbConnection::readVersion(){
	
	sqlite3_stmt *pStmt;
	const char *zErrMsg= 0; 

	std::string selectSql = "SELECT VALUE FROM METADATA WHERE ID='VERSION'";

	int rc = sqlite3_prepare_v2(db, selectSql.c_str(), -1, &pStmt,&zErrMsg);

	if(rc == SQLITE_OK)
	{		
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			const unsigned char * tmp = sqlite3_column_text(pStmt, 0);
			if ( tmp != 0 ) { 
				std :: cout << "read version: " << tmp << std::endl;
				version = std::string ( (const char *) tmp );
			}
		}
	}else{

		// no need of log
		// test of invariant

		return false;
	}
	sqlite3_finalize(pStmt);
	return version.compare(VERSIONHARDCODED) == 0;
}

void DbConnection::createSchema(){
	std::ifstream infile( sqlschemafileName.c_str() );
	std::string line = "";
	std::string sql ="" ;
	std::vector<std::string> vect;
	const char *sqlCreate;
	char *zErrMsg = 0;
	
	if ( ! infile.is_open() ) {
		throw DbConnectionException ( "Unable to open : " + sqlschemafileName );
	}else{
		std::cerr << "Load file: " << sqlschemafileName << std::endl;
	};

	while (getline(infile, line)){
		sql = sql + line;
		if ( line.find(");") != std::string::npos)
		{
			vect.push_back(sql);				
			sql ="";
		};
    };

	for (size_t i=0;i < vect.size();i++){
		sqlCreate = vect[i].c_str();
		//std::cout << "ALLSQL FILE:"  << vect[i] << std::endl;
		
		int rc = sqlite3_exec(db, sqlCreate, NULL, 0, &zErrMsg);

		if (rc!=SQLITE_OK ){			
				std::string error ( sqlite3_errmsg(db) );	
				throw DbConnectionException ( "SQL error :" + error + " ->" + vect[i] );
		}	
	}
	
}

DbConnectionException::DbConnectionException(std::string msg):message(msg){
}

DbConnectionException::~DbConnectionException(){
}

void DbConnectionException::print(){
	std::cerr << "DBCONNECTION ERROR:" <<message << std::endl;
}