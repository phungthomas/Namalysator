#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <configparser.h>
#include <parserCheck.h>
#include "inventoryparser.h"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "sqlloadinventory.h"

namespace fs = boost::filesystem;


int loadInventory (const char * fileName,SQLLoadInventory& db ){

	int skipfirst = 0;

	




	db.startTransaction();
	SQLLoad sql = db.getSQLLoad();
    sql.Start();

	inventoryparser inventoryp(&sql);
	parserCheck parser;
	parser.setContentHandler(&inventoryp);

	if(parser.parse(fileName)!=0){
		std::cerr << "inventoryFile :" << fileName << std::endl;
		return -1;
	}
		
	//sql.Store(all_words);
    

	db.endTransaction();

	return 0;
}

int start(){
	//get current path of the folder
	fs::path CurrentPath( fs::initial_path<fs::path>());
	
	std::stringstream configPath,sqlCreateTablePath;	
	configPath << CurrentPath << "/config.xml"; 	

	Parameters parameter;

	configparser config(&parameter);
	//Parse the config file
	
	std::cerr << "Config file :" << configPath.str().c_str() << std::endl;

	if (config.parse(configPath.str().c_str()) !=0 )	
	{	
		std::cerr << "Unable to parse :" << configPath << std::endl;
		return 1;				
	}
	std::cerr << parameter.getValue("database")+ ".db" << std::endl;

	int ret;
	std :: cout << "Inventory loader" << std::endl;
	SQLLoadInventory db ( parameter.getValue("database") + ".db" ,"createTable.txt" );
	try {
		db.openDB();
		ret = loadInventory(parameter.getValue("inventoryFile").c_str(), db);
		db.closeDB();
		return ret;
	}catch(DbConnectionException& e){
		e.print();
	}
	return -1;
}

int main () {
	int ret;
	XMLPlatformUtils::Initialize ();
	
	ret=start();
	
	XMLPlatformUtils::Terminate ();
    return ret;
}