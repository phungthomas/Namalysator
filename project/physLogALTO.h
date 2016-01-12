#ifndef STRUCTSEQUENCEMAP_H
#define STRUCTSEQUENCEMAP_H

#include <string>
#include <list>
#include <map>



// this class is a helper to build the structure needed by a filter for the percentage of coverage
// Main Algo :
// -- build a sequence of all physical pages
// -- maintain a map of all pages returning true on the isCheckedType ( mainly returning true when type contain the string MAIN )
// -- build a map with true for the all intervall containing interesting page
// Option : a do nothing flag if we don't want the check provide 
// in that case 

class PhysicalLogicalAltoFilter {
public :
	PhysicalLogicalAltoFilter();
	void appendPhysical( std::string key );
	void checkLogical( std::string key , std::string type );
	bool isAltoToCheck(std::string key);
	void build();

	void setDoNothing(bool flag=true);

	virtual bool isCheckedType(std::string type); 
private :
	std::map<std::string,bool> mapKey;
	std::list<std::string> listKey;
	bool donothing; 
};

#endif