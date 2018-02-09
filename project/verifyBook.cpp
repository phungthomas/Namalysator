#include "verifybook.h"
#include <iostream>
#include "inventory.h"
#include <sstream>



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

	if ( invent.publisher.compare(context.inventory.inventoryMODSMD_PRINT.publisher)) {
		hError -> getError(cat_bookinventoryTitle,"METS","DMDSEC MODSMD_PRINT", "wrong publisher:" + context.inventory.inventoryMODSMD_PRINT.publisher +" against :"+ invent.publisher ,context.currentMetsFile,context.inventory.inventoryMODSMD_PRINT.publisher);
	}

	if ( invent.printer.compare(context.inventory.inventoryMODSMD_PRINT.printer)) {
		hError -> getError(cat_bookinventoryTitle,"METS","DMDSEC MODSMD_PRINT", "wrong printer:" + context.inventory.inventoryMODSMD_PRINT.printer +" against :"+ invent.printer ,context.currentMetsFile,context.inventory.inventoryMODSMD_PRINT.printer);
	}

	
	if ( invent.callnumber.compare(context.inventory.inventoryMODSMD_PRINT.callnumber)) {
		hError -> getError(cat_bookinventoryTitle,"METS","DMDSEC MODSMD_PRINT", "wrong callNumber:" + context.inventory.inventoryMODSMD_PRINT.callnumber +" against :"+ invent.callnumber ,context.currentMetsFile,context.inventory.inventoryMODSMD_PRINT.callnumber);
	}


	string partNumberBuild = buildPartNumber(invent.yearnumber,invent.issuenumber);
	if ( partNumberBuild . compare(context.inventory.inventoryMODSMD_PRINT.partNumber)){
		hError -> getError(cat_bookinventoryTitle,"METS","DMDSEC MODSMD_PRINT", "wrong partNumber:" + context.inventory.inventoryMODSMD_PRINT.partNumber +" against :"+ partNumberBuild ,context.currentMetsFile,context.inventory.inventoryMODSMD_PRINT.partNumber);	
	}


	
	// TODO compare must be base on any kind order of list

	for ( std::map<std::string,std::string>::iterator it = context.inventory.inventoryMODSMD_PRINT.languageTerm.begin() ; it != context.inventory.inventoryMODSMD_PRINT.languageTerm.end() ;it++){

		if ( invent.languageTerm.find(it->first) == invent.languageTerm.end() ) {
			hError -> getError(cat_bookinventoryData,"METS","DMDSEC MODSMD_PRINT", "wrong languageTerm:" + it->first ,context.currentMetsFile,it->first);
			
		}
	
	};


}

std::string verifyBook::buildPartNumber(std::string& yearNumber, std::string& issueNumber){

	// Generation of : Jg. @yearNumber@, n° @issueNumber@
	int yearLen = yearNumber.length();
	int issueLen =	issueNumber.length();

	std::cout << "YEAR NUMBER:" << yearNumber << std::endl;
	std::cout << "ISSUE NUMBER:" << issueNumber << std::endl;

	std::stringstream ss;
	if ( yearLen != 0 ){
		ss << "Jg. " << yearNumber;
	}

	if ( issueLen != 0){
		if ( yearLen != 0 ){ // ADD COMMA
			ss << ", ";
		}

		ss << "n°" << issueNumber;
	}

	std::cout << "RESULTE" << ss.str() << std::endl;

	return ss.str();
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
