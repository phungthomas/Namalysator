#ifndef COMMON_H__
#define COMMON_H__

#include <map>
#include <string>


class Parameters
{
public:
	static const std::string prefix;
	virtual void addParam(std::string Key,std::string Val); 
	virtual std::string getValue(std::string Key);
	virtual int getValueCheck(std::string Key); // add prefix "verifiers." to the key and give an atoi of the associate value
	virtual std::map<std::string,std::string> mapFilter(); //extract all key starting by prefix "verifiers." and remove this part
	
private :
	std::map<std::string,std::string> mapConfig;
	std::map<std::string,int> getValueCheckCache; // cache only for getValueCheck
};
#endif