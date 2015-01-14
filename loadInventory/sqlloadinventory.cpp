#include "sqlloadinventory.h"

SQLLoadInventory::SQLLoadInventory(std::string _dbfileName, std::string _sqlschemafileName):DbConnection(_dbfileName,_sqlschemafileName){
}
SQLLoadInventory::~SQLLoadInventory(){
}