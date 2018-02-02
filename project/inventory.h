#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <string>
#include <map>


//+ struct inventaire : define field for an inventaire
// keep original naming of field.

class inventory{
public:
	std::string author;
	std::string title;
	std::string titlecollection;
	std::string subtitle;
	std::string paperid;
	std::string barcode;
	std::string issuenumber;
	std::string formaldate;
	std::string type;
	std::string uniquebuildkey;
	std::map<std::string,std::string> languageTerm; 
	std::string toString(std::string name);
	int checked;
};

// inventoryMapping : store different inventory like there is multiple section in xml 
class inventoryMapping {
private :

	inventory* currentInventory;
public :
	inventory inventoryMODSMD_PRINT;
	inventory inventoryMODSMD_COLLECTION;
	inventory inventoryMARCMD_ALEPHSYNC;

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