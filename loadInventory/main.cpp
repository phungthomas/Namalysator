#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

int loadInventory (const char * fileName ){

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
	std :: cout << "Inventory loader" << std::endl;
    return loadInventory("file.csv");
}