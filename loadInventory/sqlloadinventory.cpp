#include <iostream>
#include "sqlloadinventory.h"

SQLLoad::SQLLoad(){
}

SQLLoad::~SQLLoad(){
}

void SQLLoad::Start(){
}

void SQLLoad::Store(std::vector<std::string> allValue){
	std::cerr << allValue.size() << std::endl;
}

SQLLoadInventory::SQLLoadInventory(std::string _dbfileName, std::string _sqlschemafileName):DbConnection(_dbfileName,_sqlschemafileName){
}

SQLLoadInventory::~SQLLoadInventory(){
}

