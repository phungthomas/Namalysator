#include "inventory.h"
#include <sstream>
#include <iostream>


std::string inventory::toString(std::string name){
	std::stringstream ss;
	ss<<"INVENTORY:"<<name<<std::endl;
	ss<<"BIBREC_245a:"<<BIBREC_245a<<std::endl;
	ss<<"BIBREC_245b:"<<BIBREC_245b<<std::endl;
	ss<<"BIBREC_100a_1:"<<BIBREC_100a_1<<std::endl;
	ss<<"BIBREC_100a_2:"<<BIBREC_100a_2<<std::endl;
	ss<<"BIBREC_260b:"<<BIBREC_260b<<std::endl;
	ss<<"BIBREC_260c:"<<BIBREC_260c<<std::endl;
	//ss<<"ITEM_barcode:"<<ITEM_barcode<<std::endl;
	ss<<"BIBREC_SYS_NUM:"<<BIBREC_SYS_NUM<<std::endl;
	ss<<"languageTerm:"<<languageTerm<<std::endl;//ss<<"BIBREC_008_35_37:"<<BIBREC_008_35_37<<std::endl;
	ss<<"END INVENTORY:"<<name<<std::endl;
	return ss.str();
}

std::string inventoryMapping::toString(){
	return  inventoryMODSMD_PRINT.toString("MODSMD_PRINT") +
			inventoryMODSMD_ELEC.toString("MODSMD_ELEC")+
			inventoryMARCMD_ALEPHSYNC.toString("MARCMD_ALEPHSYNC");
}

inventory* inventoryMapping::getInventory(std::string type){
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
	if ( field.compare("BIBREC_245b")==0 ) currentInventory->BIBREC_245b=value;
	if ( field.compare("BIBREC_100a-1")==0) currentInventory->BIBREC_100a_1=value;
	if ( field.compare("BIBREC_100a-2")==0) currentInventory->BIBREC_100a_2=value;
	if ( field.compare("BIBREC_260b")==0) currentInventory->BIBREC_260b=value;
	if ( field.compare("BIBREC_260c")==0) currentInventory->BIBREC_260c=value;
	//if ( field.compare("ITEM_barcode")==0) currentInventory->ITEM_barcode=value;
	if ( field.compare("BIBREC_SYS_NUM")==0) currentInventory->BIBREC_SYS_NUM=value;
	if ( field.compare("languageTerm")==0) currentInventory->languageTerm=value;//if ( field.compare("BIBREC_008_35-37")==0) currentInventory->BIBREC_008_35_37=value;
}


void inventoryMappingActif::setCurrentInventory(std::string type){ // call parent if actif, otherwise do nothing
	if ( actif ) inventoryMapping::setCurrentInventory(type);
}
void inventoryMappingActif::setCurrentInventoryValue(std::string field, std::string value){ // call parent if actif, otherwise do nothing
	if ( actif ) inventoryMapping::setCurrentInventoryValue(field,value);
}

void inventoryMappingActif::setActif(bool _actif){
	std::cerr << "INVENTORY SET to : " << _actif << std::endl;
	actif = _actif;
}

bool inventoryMappingActif::isActif(){
	return actif;
}