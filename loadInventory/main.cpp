#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "sqlloadinventory.h"

int loadInventory (const char * fileName,DbConnection& db ){

	std::ifstream infile(fileName);
	std::string line = "";
	
	if ( ! infile.is_open() ) {
		std::cerr << "File ["<<fileName<<"] doesn't exist "<< std::endl;
		return -1;
	} 
    while (getline(infile, line)){
		std::stringstream strstr(line);
		std::string word = "";
		std::vector<std::string> all_words;

		while (getline(strstr,word, ';')) { 
			all_words.push_back(word);
			//std::cout << "FILEWORD:" << word << std::endl; 
		}
    }

	return 0;
}


int main () {
	int ret;
	std :: cout << "Inventory loader" << std::endl;
	SQLLoadInventory db ( "test.db","createTable.txt" );
	try {
		db.openDB();
		ret = loadInventory("file.csv", db);
		db.closeDB();
		return ret;
	}catch(DbConnectionException& e){
		e.print();
	}
    return -1;
}