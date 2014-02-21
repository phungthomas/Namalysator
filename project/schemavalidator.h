#ifndef SCHEMAVALIDATOR_H_
#define SCHEMAVALIDATOR_H_

#include "../common_files/struct.h"

class schemavalidator
{
public:
	virtual ~schemavalidator() {};
	virtual Error validate(const std::string &data,int lineError) = 0;
};

#endif // SCHEMAVALIDATOR_H_