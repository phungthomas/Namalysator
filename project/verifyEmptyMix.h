#ifndef VERIFYEMPTYMIX_H
#define VERIFYEMPTYMIX_H

#include "verifybook.h"

class verifyEmptyMix : public verifyBook {

	public :
	verifyEmptyMix();
	virtual void check(int,metsparserContext&);

};

#endif
