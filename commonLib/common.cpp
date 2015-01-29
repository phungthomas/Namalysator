#include "common.h"
#include <iostream>

const std::string Parameters::prefix="verifiers.";

void Parameters::addParam(std::string Key,std::string Val){
	
	mapConfig[Key]+=Val;
	//std::cerr << "KEY:"<<Key <<" VALUE:"<< Val<< " LENGTH:" <<mapConfig[Key].length()<<std::endl;
}

std::string Parameters::getValue(std::string Key){
	std::map<std::string,std::string>::iterator it=mapConfig.find(Key);
	if ( it == mapConfig.end() ) { 
		std::cerr << "KEY NOT FOUND:"<<Key<<std::endl; 
		return "";
	}
	else return it->second;
}

int Parameters::getValueCheck(std::string _Key){
	std::string key = prefix+_Key;
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

std::map<std::string,std::string> Parameters::mapFilter(){
	
	std::map<std::string,std::string> ret;
	for ( std::map<std::string,std::string>::iterator it = mapConfig.begin();it != mapConfig.end() ;it++){
		std::string key = it->first;
		if ( prefix.compare(0,prefix.length(),key,0,prefix.length()) == 0){
			ret[key.substr(prefix.length())]=it->second;
		}

	}
	return ret;
}