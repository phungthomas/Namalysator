#include <iostream>
#include "sqlloadinventory.h"

SQLLoad::SQLLoad():zErrMsg(0),pStmt(0){
	sql = "INSERT INTO BOOKSINVENTORY "
		              "( BOX_ID,BIBREC_SYS_NUM,ITEM_barcode,BIBREC_CALL_NUM,"
		              "  languageTerm,BIBREC_008_7_10,BIBREC_100a,BIBREC_245a,"
					  "  BIBREC_260b) "
		              "VALUES (?,?,?,?,?,?,?,?,?);";
}

SQLLoad::~SQLLoad(){
	if (pStmt)sqlite3_finalize(pStmt);
}

void SQLLoad::Start(){
	int rc ;
	if ( pStmt == 0 ) {
		if ( (rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &pStmt, &zErrMsg)) != SQLITE_OK){
			std::string error ( sqlite3_errmsg(db) );
			std :: cerr << rc << std::endl;
			throw DbConnectionException ( "SQL PREPARE ERROR on : \n" + sql + "\n" + error ); 
		}
	}else{
		sqlite3_reset(pStmt);
	}
}

void SQLLoad::Store(std::vector<std::string> allValue){
	//std::cerr << allValue.size() << std::endl;
	if ( allValue.size() != 10 ){
		std::cerr << "Not enough field in file : " << allValue.size() << std::endl;
		return ;
	};
	sqlite3_clear_bindings(pStmt);
	sqlite3_reset(pStmt);
    
	int pt = 0;
	int vt = 0;
	for ( int i = 0; i < allValue.size(); i++){
		if ( i == 1 ) { // skip second column
			vt ++;
			continue;
		};
		pt++;
		//std::cerr << "VAL" << pt <<" :" << allValue[vt] << std::endl;//DEBUG
		if ( vt!= 5 || allValue[vt].length() != 0 ) { // skip error on inventory
			sqlite3_bind_text(pStmt, pt, allValue[vt].c_str(),allValue[vt].length(),SQLITE_STATIC);
		}
		vt++;
	}

	if (sqlite3_step(pStmt) != SQLITE_DONE) {
		std::string error ( sqlite3_errmsg(db) );
		std::cerr << error << std::endl;
		std::cerr << "SYSNUM " << allValue[1] << std::endl;
		std::cerr << sql << std::endl;
		
		for ( int i = 0; i < allValue.size(); i++){
			if ( i==2) continue;
			std::cerr << "'" << allValue[i] << "'," ;
		}
		std::cerr << std::endl;
	};
	
}

SQLLoadInventory::SQLLoadInventory(std::string _dbfileName, std::string _sqlschemafileName):DbConnection(_dbfileName,_sqlschemafileName){
}

SQLLoadInventory::~SQLLoadInventory(){
}
SQLLoad& SQLLoadInventory::getSQLLoad(){
	sqlLoad.db = db;
	return sqlLoad; 
};

