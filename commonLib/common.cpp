#include "common.h"
#include <iostream>

void Parameters::setValue(std::string Key,std::string Val){
	//mapConfig.insert( std::pair<std::string,std::string>(Key,Val));
	mapConfig[Key]+=Val;
	std::cerr << "KEY:"<<Key <<" VALUE:"<< Val<< " LENGTH:" <<mapConfig[Key].length()<<std::endl;
}

std::string Parameters::getValue(std::string Key){
	std::map<std::string,std::string>::iterator it=mapConfig.find(Key);
	if ( it == mapConfig.end() ) { return "";}
	else return it->second;
}

int Parameters::getValueCheck(std::string _Key){
	std::string key = "verifiers."+_Key;
	std::map<std::string,int>::iterator it= getValueCheckCache.find(key);
	if ( it != getValueCheckCache.end() ) {
		return it->second;
	}

	std::map<std::string,std::string>::iterator iti=mapConfig.find(key);
	if ( iti == mapConfig.end() ) {
		std::cerr << "CONFIGKEY NOT DEFINE:"<<key<< " set to default 0" << std::endl;
		getValueCheckCache[key]=0; // define default
		mapConfig[key]="0"; // completude
		return 0;
	}

	int ret = atoi ( (iti->second).c_str() );
	getValueCheckCache[key]=ret;

	return ret;
}