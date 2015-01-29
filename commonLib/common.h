#ifndef COMMON_H__
#define COMMON_H__

#include <map>
#include <string>

class Parameters
{
public:
	void setValue(std::string Key,std::string Val);
	std::string getValue(std::string Key);
	int getValueCheck(std::string Key);
private :
	std::map<std::string,std::string> mapConfig;
	std::map<std::string,int> getValueCheckCache; // cache only for getValueCheck
};
#endif