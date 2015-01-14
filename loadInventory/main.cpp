#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <configparser.h>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "sqlloadinventory.h"

namespace fs = boost::filesystem;

// analyse csv file separate by ;
// xxxx;xxxx;"xxxxx";"yyyy;xxxx";"zzzz"" ;""kjhkhkjhkj";xxxxx

void analyse ( const char* line, std::vector<std::string> & vect  ){
    static char WORD [ 2000 ]; // not nice
	const char * ptr ;
	char * ptrW ;
	int mode=0;

	ptr = line;
	ptrW = WORD; *ptrW = '\0' ;
	

	for ( ptr = line ; *ptr ; ptr++ ) {
	
		switch ( *ptr ) {
		case	';' : 
			      if ( mode == 2 ){
					// escape mode : true ';' in the content ( not a separator of field )
					*ptrW = *ptr; ptrW++;
				  }else{
					// new WORD START
					// means previous is finish
					*ptrW = '\0' ; 
					vect.push_back(std::string(WORD));
					ptrW = WORD; *ptrW = '\0' ;
					mode = 1;
				  }
				  break;
		case '"' : 
					switch ( mode ) {
						case 1 :
							mode = 2;
							break;
						case 2 :
							mode = 3; // perhaps suite of "", but could be "; 
							break;
						case 3 :
							mode = 2; // but copy the " like it is a suite "" 
						case 0 :
							*ptrW = *ptr; ptrW++;
							break;
					}
	
					break;
		default :
		          *ptrW = *ptr; ptrW++;  
				  if ( mode == 1 ) {
					  mode = 0;
				  }
				  break;
		}
	}
	// always add last one;
	vect.push_back( std::string(WORD) );
}

int loadInventory (const char * fileName,SQLLoadInventory& db ){

	int skipfirst = 0;
	std::ifstream infile(fileName);
	std::string line = "";
	
	if ( ! infile.is_open() ) {
		std::cerr << "File ["<<fileName<<"] doesn't exist "<< std::endl;
		return -1;
	} 
	db.startTransaction();
	SQLLoad sql = db.getSQLLoad();
    sql.Start();

    while (getline(infile, line)){
		std::stringstream strstr(line);
		std::string word = "";
		std::vector<std::string> all_words;

		
		skipfirst ++ ;
		if ( skipfirst == 1 ) continue;

		analyse (line.c_str(),all_words);

		//std::cerr << "Line :" << skipfirst << " -> " << std::endl;
		sql.Store(all_words);
    }

	db.endTransaction();

	return 0;
}



int main () {
	
	XMLPlatformUtils::Initialize ();
	
	//get current path of the folder
	fs::path CurrentPath( fs::initial_path<fs::path>());
	
	std::stringstream configPath,sqlCreateTablePath;	
	configPath << CurrentPath << "/config.xml"; 	

	Parameters *parameter = new Parameters;

	configparser config(parameter);
	//Parse the config file
	
	std::cerr << "Config file :" << configPath.str().c_str() << std::endl;

	if (config.parse(configPath.str().c_str()) !=0 )	
	{	
		std::cerr << "Unable to parse :" << configPath << std::endl;
		return 1;				
	}

	int ret;
	std :: cout << "Inventory loader" << std::endl;
	SQLLoadInventory db ( parameter->database + ".db" ,"createTable.txt" );
	try {
		db.openDB();
		ret = loadInventory(parameter->inventoryFile.c_str(), db);
		db.closeDB();
		return ret;
	}catch(DbConnectionException& e){
		e.print();
	}
	XMLPlatformUtils::Terminate ();
    return -1;
}