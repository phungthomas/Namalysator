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
	std::string BIBREC_SYSNUM = context.inventory.inventoryMODSMD_ELEC.BIBREC_SYS_NUM;
	if (!db->getInventory(BIBREC_SYSNUM,invent)){
		hError -> getError(cat_bookinventory,"METS","DMDSEC MODSMD_ELEC", "BIBREC_SYSNUM not found:" + BIBREC_SYSNUM ,context.currentMetsFile,BIBREC_SYSNUM);
		return; // skip all
	};

	db->InventoryChecked(BIBREC_SYSNUM); // update checked flag in bookinventory to be able to show the rate of full campaign

	if ( invent.BIBREC_245a.compare(context.inventory.inventoryMODSMD_ELEC.BIBREC_245a)) {
		hError -> getError(cat_bookinventoryTitle,"METS","DMDSEC MODSMD_ELEC", "wrong title:" + context.inventory.inventoryMODSMD_ELEC.BIBREC_245a +" against :"+ invent.BIBREC_245a ,context.currentMetsFile,context.inventory.inventoryMODSMD_ELEC.BIBREC_245a);
	}


	if ( invent.BIBREC_245a.compare(context.inventory.inventoryMODSMD_PRINT.BIBREC_245a)) {
		hError -> getError(cat_bookinventoryTitle,"METS","DMDSEC MODSMD_PRINT", "wrong title:" + context.inventory.inventoryMODSMD_PRINT.BIBREC_245a +" against :"+ invent.BIBREC_245a,context.currentMetsFile,context.inventory.inventoryMODSMD_PRINT.BIBREC_245a);
	}


	if ( invent.BIBREC_100a.compare(context.inventory.inventoryMODSMD_ELEC.BIBREC_100a)) {
		hError -> getError(cat_bookinventoryData,"METS","DMDSEC MODSMD_ELEC", "wrong BIBREC_100a:" + context.inventory.inventoryMODSMD_ELEC.BIBREC_100a +" against :"+ invent.BIBREC_100a,context.currentMetsFile,context.inventory.inventoryMODSMD_ELEC.BIBREC_100a);
	}

	if ( invent.BIBREC_100a.compare(context.inventory.inventoryMODSMD_PRINT.BIBREC_100a)) {
		hError -> getError(cat_bookinventoryData,"METS","DMDSEC MODSMD_PRINT", "wrong BIBREC_100a:" + context.inventory.inventoryMODSMD_PRINT.BIBREC_100a +" against :"+ invent.BIBREC_100a ,context.currentMetsFile,context.inventory.inventoryMODSMD_PRINT.BIBREC_100a);
	}
	
	// TODO compare must be base on any kind order of list
	
	for ( std::map<std::string,std::string>::iterator it = context.inventory.inventoryMODSMD_ELEC.languageTerm.begin() ; it != context.inventory.inventoryMODSMD_ELEC.languageTerm.end() ;it++){

		if ( invent.languageTerm.find(it->first) == invent.languageTerm.end() ) {
			hError -> getError(cat_bookinventoryData,"METS","DMDSEC MODSMD_ELEC", "wrong languageTerm:" + it->first ,context.currentMetsFile,it->first);
			
		}
	
	};

	for ( std::map<std::string,std::string>::iterator it = context.inventory.inventoryMODSMD_PRINT.languageTerm.begin() ; it != context.inventory.inventoryMODSMD_PRINT.languageTerm.end() ;it++){

		if ( invent.languageTerm.find(it->first) == invent.languageTerm.end() ) {
			hError -> getError(cat_bookinventoryData,"METS","DMDSEC MODSMD_PRINT", "wrong languageTerm:" + it->first ,context.currentMetsFile,it->first);
			
		}
	
	};

	for ( std::map<std::string,std::string>::iterator it = invent.languageTerm.begin() ; it != invent.languageTerm.end(); it++ ){

		if ( context.inventory.inventoryMODSMD_PRINT.languageTerm.find(it->first) == context.inventory.inventoryMODSMD_PRINT.languageTerm.end() ){
			hError -> getError(cat_bookinventoryData,"METS","DMDSEC MOD_SMD_PRINT", "wrong languageTerm:not present" + it->first ,context.currentMetsFile,it->first);
		};

		if ( context.inventory.inventoryMODSMD_ELEC.languageTerm.find(it->first) == context.inventory.inventoryMODSMD_ELEC.languageTerm.end() ){
			hError -> getError(cat_bookinventoryData,"METS","DMDSEC MODSMD_ELEC", "wrong languageTerm:not present" + it->first ,context.currentMetsFile,it->first);
		};
	};


	if ( invent.ITEM_barcode.compare(context.inventory.inventoryMODSMD_PRINT.BIBREC_SYS_NUM /* put there in the xml */ )) {
		hError -> getError(cat_bookinventoryData,"METS","DMDSEC MODSMD_PRINT", "wrong BARCODE:" + context.inventory.inventoryMODSMD_PRINT.BIBREC_SYS_NUM +" against :"+ invent.ITEM_barcode,context.currentMetsFile,context.inventory.inventoryMODSMD_PRINT.BIBREC_SYS_NUM);
	}

	if ( invent.BIBREC_260b.compare(context.inventory.inventoryMODSMD_PRINT.BIBREC_260b  )) {
		hError -> getError(cat_bookinventoryData,"METS","DMDSEC MODSMD_PRINT", "wrong BIBREC_260b:" + context.inventory.inventoryMODSMD_PRINT.BIBREC_260b +" against :"+ invent.BIBREC_260b ,context.currentMetsFile,context.inventory.inventoryMODSMD_PRINT.BIBREC_260b);
	}

	if ( invent.BIBREC_SYS_NUM.compare(context.inventory.inventoryMARCMD_ALEPHSYNC.BIBREC_SYS_NUM )) {
		hError -> getError(cat_bookinventoryData,"METS","DMDSEC MARCMD_ALEPHSYNC", "wrong BIBREC_SYS_NUM:" + context.inventory.inventoryMARCMD_ALEPHSYNC.BIBREC_SYS_NUM +" against :"+ invent.BIBREC_SYS_NUM,context.currentMetsFile,context.inventory.inventoryMARCMD_ALEPHSYNC.BIBREC_SYS_NUM);
	}

}

void verifyBook::init(metsparserContext& context){
	hError = context.hError;
	db = hError -> getDatabase();
}
