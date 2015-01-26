#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <string>


//+ struct inventaire : define field for an inventaire
// keep original naming of field.

struct inventory{
	std::string BIBREC_245a;
	std::string BIBREC_245b;
	std::string BIBREC_100a_1;
	std::string BIBREC_100a_2;
	std::string BIBREC_008_35_37;
	std::string BIBREC_260b;
	std::string BIBREC_260c;
	std::string ITEM_barcode;
	std::string BIBREC_SYS_NUM;
};

// inventoryMapping : store different inventory like there is multiple section in xml 
class inventoryMapping {
private :
	struct inventory inventoryMODSMD_PRINT;
	struct inventory inventoryMODSMD_ELEC;
	struct inventory inventoryMARCMD_ALEPHSYNC;
	struct inventory* currentInventory;
public :
	struct inventory* getInventory(std::string type);
	virtual void setCurrentInventory(std::string type);
	virtual void setCurrentInventoryValue(std::string field, std::string value);
};

// do the work only if actif : meaning if it is a monography

class inventoryMappingActif:public inventoryMapping{

	bool actif;

public :

	virtual void setCurrentInventory(std::string type); // call parent if actif, otherwise do nothing
	virtual void setCurrentInventoryValue(std::string field, std::string value); // call parent if actif, otherwise do nothing
    void setActif(bool);
};

#endif