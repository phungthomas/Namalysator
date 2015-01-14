#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "sqlloadinventory.h"

// analyse csv file separate by ;
// xxxx;xxxx;"xxxxx";"yyyy;xxxx";"zzzz"" ;""kjhkhkjhkj";xxxxx

void analyse ( const char* line, std::vector<std::string> & vect  ){
    static char WORD [ 1000 ];
	const char * ptr ;
	char * ptrW ;
	int mode=0;

	ptr = line;
	ptrW = WORD; *ptrW = '\0' ;
	

	for ( ptr = line ; *ptr ; ptr++ ) {
	
		switch ( *ptr ) {
		case	';' : 
			      if ( mode == 2 ){
					// escape mode : true ; in the content ( not a separator of field )
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
							mode = 2; // but copy the " 
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
	SQLLoad sql = db.getSQLLoad();
    sql.Start();

    while (getline(infile, line)){
		std::stringstream strstr(line);
		std::string word = "";
		std::vector<std::string> all_words;

		
		skipfirst ++ ;
		if ( skipfirst == 1 ) continue;

		analyse (line.c_str(),all_words);

		std::cerr << "Ligne :" << skipfirst << " -> ";
		sql.Store(all_words);
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