#include "verifybook.h"
#include <iostream>
#include "inventory.h"



verifyBook::verifyBook(){
	//std::cerr << "VERIFY BOOK" << std::endl;
}

void verifyBook::check(int check,metsparserContext& context){

	if ( check != 1 ) return; 
	init (context);

	// check if BIBREC_SYSNUM in database
	std::string UNIQ = context.inventory.inventoryMODSMD_PRINT.uniquebuildkey; // MUST depend from type
	if (!db->getInventory(UNIQ,invent)){
		hError -> getError(cat_bookinventory,"METS","DMDSEC MODSMD_PRINT", "UNIQKEY not found:" + UNIQ ,context.currentMetsFile,UNIQ);
		return; // skip all
	};

	db->InventoryChecked(UNIQ); // update checked flag in bookinventory to be able to show the rate of full campaign

	std::string title = buildTitle( context.inventory.inventoryMODSMD_PRINT);
	if ( invent.title.compare(title)) {
		hError -> getError(cat_bookinventoryTitle,"METS","DMDSEC MODSMD_PRINT", "wrong title:" + context.inventory.inventoryMODSMD_PRINT.title +" against :"+ invent.title ,context.currentMetsFile,context.inventory.inventoryMODSMD_PRINT.title);
	}

    title = buildTitle( context.inventory.inventoryMODSMD_COLLECTION); // in the xml in title
	if ( invent.titlecollection.compare(title)) {
		hError -> getError(cat_bookinventoryTitle,"METS","DMDSEC MODSMD_COLLECTION", "wrong title collection:" + context.inventory.inventoryMODSMD_COLLECTION.title +" against :"+ invent.titlecollection ,context.currentMetsFile,context.inventory.inventoryMODSMD_COLLECTION.title);
	}

	/* //TODO rebuild all those test

    title = buildTitle( context.inventory.inventoryMODSMD_PRINT);
	if ( invent.BIBREC_245a.compare(title)) {
		hError -> getError(cat_bookinventoryTitle,"METS","DMDSEC MODSMD_PRINT", "wrong title:" + context.inventory.inventoryMODSMD_PRINT.BIBREC_245a +" against :"+ invent.BIBREC_245a,context.currentMetsFile,context.inventory.inventoryMODSMD_PRINT.BIBREC_245a);
	}


	if ( invent.BIBREC_100a.compare(context.inventory.inventoryMODSMD_COLLECTION.BIBREC_100a)) {
		hError -> getError(cat_bookinventoryData,"METS","DMDSEC MODSMD_COLLECTION", "wrong BIBREC_100a:" + context.inventory.inventoryMODSMD_COLLECTION.BIBREC_100a +" against :"+ invent.BIBREC_100a,context.currentMetsFile,context.inventory.inventoryMODSMD_COLLECTION.BIBREC_100a);
	}

	if ( invent.BIBREC_100a.compare(context.inventory.inventoryMODSMD_PRINT.BIBREC_100a)) {
		hError -> getError(cat_bookinventoryData,"METS","DMDSEC MODSMD_PRINT", "wrong BIBREC_100a:" + context.inventory.inventoryMODSMD_PRINT.BIBREC_100a +" against :"+ invent.BIBREC_100a ,context.currentMetsFile,context.inventory.inventoryMODSMD_PRINT.BIBREC_100a);
	}
	*/
	
	// TODO compare must be base on any kind order of list

	for ( std::map<std::string,std::string>::iterator it = context.inventory.inventoryMODSMD_PRINT.languageTerm.begin() ; it != context.inventory.inventoryMODSMD_PRINT.languageTerm.end() ;it++){

		if ( invent.languageTerm.find(it->first) == invent.languageTerm.end() ) {
			hError -> getError(cat_bookinventoryData,"METS","DMDSEC MODSMD_PRINT", "wrong languageTerm:" + it->first ,context.currentMetsFile,it->first);
			
		}
	
	};


}

std::string verifyBook::buildTitle(inventory& invent){
	
	std::string ret;

	//if ( invent.nonSort.empty()) {
		return invent.title ;
	//}
	//ret = invent.nonSort + " " + invent.BIBREC_245a;
	//return ret;
}

void verifyBook::init(metsparserContext& context){
	hError = context.hError;
	db = hError -> getDatabase();
	invent.languageTerm.clear();
}
