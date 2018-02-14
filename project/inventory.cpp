#include "inventory.h"
#include <sstream>
#include <iostream>


std::string inventory::toString(std::string name){
	std::stringstream ss;
	ss<<"INVENTORY:"<<name<<std::endl;
	ss<<"TITLE:"<<title<<std::endl;
	ss<<"SUBTITLE:"<<subtitle<<std::endl;
	ss<<"UNIQUE:"<<uniquebuildkey<<std::endl;
	
	for ( std::map<std::string,std::string>::iterator it = languageTerm.begin() ; it != languageTerm.end(); it ++) {

		ss<<"languageTerm:"<<it->first<<std::endl;
	
	}
	ss<<"AUTHOR:"<<author<<std::endl;
	ss<<"END INVENTORY:"<<name<<std::endl;
	return ss.str();
}

std::string inventoryMapping::toString(){
	return  inventoryMODSMD_PRINT.toString("MODSMD_PRINT") +
			inventoryMODSMD_COLLECTION.toString("MODSMD_COLLECTION")+
			inventoryMARCMD_ALEPHSYNC.toString("MARCMD_ALEPHSYNC");
}

inventory* inventoryMapping::getInventory(std::string type){
	if ( type.compare("MODSMD_COLLECTION")==0 ) return &inventoryMODSMD_COLLECTION;
	if ( type.compare("MODSMD_PRINT")==0) return &inventoryMODSMD_PRINT;
	if ( type.compare("MARCMD_ALEPHSYNC")==0)return &inventoryMARCMD_ALEPHSYNC;
	return 0;
}

void inventoryMapping::setCurrentInventory(std::string type){
	currentInventory = getInventory(type);
}

void inventoryMapping::setCurrentInventoryValue(std::string field, std::string value){
	if ( currentInventory == 0) return;


    if ( field.compare("identifier")==0 ) currentInventory->uniquebuildkey=value; // Attention alimenter pour les monographies
	if ( field.compare("recordIdentifier")==0 ) currentInventory->uniquebuildkey=value; // overloader pour les issues
	
	if ( field.compare("title")==0 ) currentInventory->title=value;
	if ( field.compare("subtitle")==0 ) currentInventory->subtitle=value;
	if ( field.compare("barcode")==0 ) currentInventory->barcode=value;
	if ( field.compare("identifier")==0) currentInventory->callnumber=value;
	if ( field.compare("dateIssued")==0 ) currentInventory->formaldate=value;

	if ( field.compare("publisher")==0 ) currentInventory->publisher=value;
	if ( field.compare("printer")==0 ) currentInventory->printer=value;
	if ( field.compare("yearnumber")==0 ) currentInventory->yearnumber=value;
	if ( field.compare("issuenumber")==0 ) currentInventory->issuenumber=value;
	if ( field.compare("partNumber")==0 ) currentInventory->partNumber=value;
	
	if ( field.compare("author")==0 ) currentInventory->author=value;
	
	if ( field.compare("languageTerm")==0) { 
		currentInventory->languageTerm[value]=value;//
	}
	
}


void inventoryMappingActif::setCurrentInventory(std::string type){ // call parent if actif, otherwise do nothing
	if ( actif ) inventoryMapping::setCurrentInventory(type);
}
void inventoryMappingActif::setCurrentInventoryValue(std::string field, std::string value){ // call parent if actif, otherwise do nothing
	if ( actif ) inventoryMapping::setCurrentInventoryValue(field,value);
}

void inventoryMappingActif::setActif(bool _actif){
	//std::cerr << "INVENTORY SET to : " << _actif << std::endl;
	actif = _actif;
}

bool inventoryMappingActif::isActif(){
	return actif;
}