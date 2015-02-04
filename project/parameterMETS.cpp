#include "parameterMETS.h"
#include <iostream>


const std::string ParameterMETS::XSDprefix="XSDManager.";


parserCheck* ParameterMETS::getParser(std::string Key){
	parserCheck* ret= 0;
	std::map<std::string,parserCheck*>::iterator it = parserCheckSet.find(Key);

	if ( it == parserCheckSet.end() ) {
		std::cerr << " Programm request a non define parser type:"<< Key << std::endl;
		exit (5);
	};
	return it->second;
}

void ParameterMETS::addParam(std::string Key,std::string Val){

	if ( XSDprefix.compare(0,XSDprefix.length(),Key,0,XSDprefix.length()) != 0) {
		Parameters::addParam(Key,Val);
		return ;
	}

	//std::cerr << "DEBUG:" << Key << " Val" <<Val << std::endl; 

	if (Key.compare(XSDprefix+"addXSD") == 0 ){
		addXSD (Val);
		return;
	};

	if (Key.compare(XSDprefix+"type") == 0 ){
		typeDefine (Val);
		return;
	};

	if (Key.compare(XSDprefix+"lock") == 0 ){
		lockXSD (Val);
		return;
	};

	return;
} 

ParameterMETS::ParameterMETS():currentParserCheck(0){

}

ParameterMETS::~ParameterMETS(){
	for ( std::map<std::string,parserCheck*>::iterator it = parserCheckSet.begin() ; it != parserCheckSet.end(); it ++){
		delete (it->second) ;
	}
}

void ParameterMETS::typeDefine (std::string type){
	parserCheckSet[type]= currentParserCheck= new parserCheck();
}

void ParameterMETS::addXSD (std::string filename){
	if ( currentParserCheck ) {
		currentParserCheck->addXSD(filename);
	}else {
		std::cerr << "Parser Type not define" << std::endl;
		exit(2);
	}
}

void ParameterMETS::lockXSD (std::string filename){
	if ( currentParserCheck ) {
		currentParserCheck->lockaddXSD();
		currentParserCheck = 0;
	}else {
		std::cerr << "LOCK Parser Type not define" << std::endl;
		exit(3);
	}
}