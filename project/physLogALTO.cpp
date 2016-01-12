#include "physLogALTO.h"

PhysicalLogicalAltoFilter::PhysicalLogicalAltoFilter():donothing(false){
}
void PhysicalLogicalAltoFilter::appendPhysical( std::string key ){
	mapKey[key]=false;
	listKey.push_back(key);
}
void PhysicalLogicalAltoFilter::checkLogical( std::string key , std::string type ){
	if ( isCheckedType ( type )) {
		mapKey[key]=true;
	}else{
		mapKey[key]=false;
	}
}

void PhysicalLogicalAltoFilter::build(){
	std::list<std::string>::iterator itr=listKey.rbegin();

	while ( itr != listKey.end() ){
		if ( mapKey[*itr] ) {
			bool flag=false; 
			for ( std::list<std::string>::iterator it = listKey.begin(); it != itr ; it++ ){

				if ( mapKey[*it] ) {
					flag = true;
				}

				if ( flag ) {
					mapKey[*it]=true;
				}
			}
			break;
		}
		itr ++;
	}
}

bool PhysicalLogicalAltoFilter::isAltoToCheck(std::string key){
	if ( donothing ) return true;
}

void PhysicalLogicalAltoFilter::setDoNothing(bool flag){
	donothing = false; 
}

bool PhysicalLogicalAltoFilter::isCheckedType(std::string type){
	if ( type.find("MAIN") !=std::string::npos ) {
		return true;
	}
	return false;
}