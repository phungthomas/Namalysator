#include "verifyFolder.h"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"

verifyFolder::verifyFolder(){

}

void verifyFolder::check(int check ,metsparserContext& context){
	if ( check!=1 ) return; 
	init (context);

	std::string path = context.currentMetsPath;
	std::string search = "/\\";

	int pos  = path.find_last_of(search);
	std::string bibrec = context.inventory.getInventory("MODSMD_ELEC")->BIBREC_SYS_NUM;

	if ( pos + 1 < path.length() ){ 
		std::string sub = path.substr(pos+1);
		if ( sub.compare( bibrec ) == 0 ) return ; // hoping that inventory is correcltly provided
	};

	hError->getError(cat_wrongFolderName,"METS","FOLDER", path + " is not BIBREC_SYS_NUM : "+ bibrec ,context.currentMetsFile,"");

}