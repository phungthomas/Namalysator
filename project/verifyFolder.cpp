#include "verifyFolder.h"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"

verifyFolder::verifyFolder(){

}

void verifyFolder::check(int check ,metsparserContext& context){
	if ( check!=1 ) return; 
	init (context);

	hError->getError(cat_wrongFolderName,"METS","FOLDER", "Test not yet implemented" ,context.currentMetsFile,"");

}