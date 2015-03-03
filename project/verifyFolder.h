#ifndef VERIFYFOLDER_H
#define VERIFYFOLDER_H

#include "verifybook.h"

class verifyFolder : public verifyBook {

	public :
	verifyFolder();
	virtual void check(int,metsparserContext&);

};

#endif