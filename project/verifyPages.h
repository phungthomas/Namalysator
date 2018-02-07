#ifndef _VERIFY_PAGES_H_
#define _VERIFY_PAGES_H_

#include "sql.h"
#include <string>
#include "inventory.h"
#include "errorhandler.h"

class verifyPages {
protected :
	database *db;
	inventory invent;
	errorHandler *hError;


	virtual void init(metsparserContext&);
public :
	verifyPages();
	virtual void check(int,metsparserContext&,int nbPages);

};

#endif