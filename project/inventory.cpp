#include "inventory.h"

struct inventory* inventoryMapping::getInventory(std::string type){
	if ( type.compare("MODSMD_ELEC")==0 ) return &inventoryMODSMD_ELEC;
	if ( type.compare("MODSMD_PRINT")==0) return &inventoryMODSMD_PRINT;
	if ( type.compare("MARCMD_ALEPHSYNC")==0)return &inventoryMARCMD_ALEPHSYNC;
	return 0;
}

void inventoryMapping::setCurrentInventory(std::string type){
	currentInventory = getInventory(type);
}

void inventoryMapping::setCurrentInventoryValue(std::string field, std::string value){
	if ( currentInventory == 0) return;

	if ( field.compare("BIBREC_245a")==0 ) currentInventory->BIBREC_245a=value;
	if ( field.compare("BIBREC_245b")==0 )currentInventory->BIBREC_245b=value;
	if ( field.compare("BIBREC_100a-1")==0) currentInventory->BIBREC_100a_1=value;
	if ( field.compare("BIBREC_100a-2")==0) currentInventory->BIBREC_100a_2=value;
	if ( field.compare("BIBREC_008_35-37")==0) currentInventory->BIBREC_008_35_37=value;
	if ( field.compare("BIBREC_260b")==0) currentInventory->BIBREC_260b=value;
	if ( field.compare("BIBREC_260c")==0) currentInventory->BIBREC_260c=value;
	if ( field.compare("ITEM_barcode")==0) currentInventory->ITEM_barcode=value;
	if ( field.compare("BIBREC_SYS_NUM")==0) currentInventory->BIBREC_SYS_NUM=value;
}


void inventoryMappingActif::setCurrentInventory(std::string type){ // call parent if actif, otherwise do nothing
	if ( actif ) inventoryMapping::setCurrentInventory(type);
}
void inventoryMappingActif::setCurrentInventoryValue(std::string field, std::string value){ // call parent if actif, otherwise do nothing
	if ( actif ) inventoryMapping::setCurrentInventoryValue(field,value);
}

void inventoryMappingActif::setActif(bool _actif){
	actif = _actif;
}