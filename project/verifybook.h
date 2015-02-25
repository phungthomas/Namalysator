#ifndef _VERIFY_BOOK_H_
#define _VERIFY_BOOK_H_

#include "metsparser.h"
#include "sql.h"
#include <string>
#include "inventory.h"
#include "errorhandler.h"

class verifyBook {
protected :
	database *db;
	inventory invent;
	errorHandler *hError;


	virtual void init(metsparserContext&);
public :
	verifyBook();
	virtual void check(std::string,metsparserContext&);

};

#endif