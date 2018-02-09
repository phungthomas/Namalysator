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
	std::string uniq=context.inventory.getInventory("MODSMD_PRINT")->uniquebuildkey;

	int count = 0;
	for ( char *tmp=(char*)uniq.c_str();*tmp !=0  ; tmp++){ //
		if (*tmp == '/'){
			count ++;
		}
	}

	

	if ( count < 2 ){
		inventory invent;
		if (!db->getInventory(uniq,invent)){
			hError -> getError(cat_bookinventory,"METS","DMDSEC MODSMD_PRINT", "Unable tocheck File Name:" + uniq ,context.currentMetsFile,uniq);
			return; // skip all
		};
		uniq = invent.systemnumber;
		// check mets naming file 
		if ( context.currentMetsFile.compare(uniq + "-mets.xml")!=0 ){
			hError->getError(cat_wrongFolderName,"METS","FOLDER", "Wrong Metsfile name: " + uniq + "-mets.xml" + " != Name of folder :" + context.currentMetsFile, context.currentMetsFile,"");		
		}


	}else{
		int poss = uniq.find_last_of('/');
		uniq = uniq.substr(poss+1);
	}
	if ( pos + 1 < path.length() ){ 
		std::string sub = path.substr(pos+1);
		if ( sub.compare( uniq ) == 0 ) return ; // hoping that inventory is correcltly provided
	};

	hError->getError(cat_wrongFolderName,"METS","FOLDER", "Wrong Path:"+ path + " is not UNIQ : "+ uniq ,context.currentMetsFile,uniq);

}