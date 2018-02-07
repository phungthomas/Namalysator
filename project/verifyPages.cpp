#include "verifyPages.h"
#include "metsparser.h"

verifyPages::verifyPages(){
	//std::cerr << "VERIFY BOOK" << std::endl;
}


void verifyPages::check(int check,metsparserContext& context, int nbPage){
	if ( check != 1 ) return; 
	init (context);

	std::string UNIQ = context.inventory.inventoryMODSMD_PRINT.uniquebuildkey; // MUST depend from type
	if (!db->getInventory(UNIQ,invent)){
		hError -> getError(cat_bookinventory,"METS","DMDSEC MODSMD_PRINT", "UNIQKEY not found:" + UNIQ ,context.currentMetsFile,UNIQ);
		return; // skip all
	};

	if ( atoi(invent.pages.c_str()) != nbPage){
		hError -> getError(cat_inventorynbpages,"METS","DMDSEC MODSMD_PRINT", "BAD NUMBER OF Pages " + invent.pages ,context.currentMetsFile,UNIQ);
		
	}

}

void verifyPages::init(metsparserContext& context){
	hError = context.hError;
	db = hError -> getDatabase();
	invent.languageTerm.clear();
}