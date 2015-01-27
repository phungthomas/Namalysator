#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <string>


//+ struct inventaire : define field for an inventaire
// keep original naming of field.

class inventory{
public:
	std::string BIBREC_245a;
	std::string BIBREC_245b;
	std::string BIBREC_100a_1;
	std::string BIBREC_100a_2;
	std::string BIBREC_260b;
	std::string BIBREC_260c;
	std::string ITEM_barcode;
	std::string BIBREC_SYS_NUM;
	std::string languageTerm; //std::string BIBREC_008_35_37;
	std::string toString(std::string name);
};

// inventoryMapping : store different inventory like there is multiple section in xml 
class inventoryMapping {
private :
	inventory inventoryMODSMD_PRINT;
	inventory inventoryMODSMD_ELEC;
	inventory inventoryMARCMD_ALEPHSYNC;
	inventory* currentInventory;
public :
	inventory* getInventory(std::string type);
	virtual void setCurrentInventory(std::string type);
	virtual void setCurrentInventoryValue(std::string field, std::string value);
	std::string toString();
};

// do the work only if actif : meaning if it is a monography

class inventoryMappingActif:public inventoryMapping{
	bool actif;
public :
	virtual void setCurrentInventory(std::string type); // call parent if actif, otherwise do nothing
	virtual void setCurrentInventoryValue(std::string field, std::string value); // call parent if actif, otherwise do nothing
    void setActif(bool);
	bool isActif();
};

#endif