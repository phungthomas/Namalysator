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
	std::string buildTitle(inventory&);
public :
	verifyBook();
	virtual void check(int,metsparserContext&);

};

#endif