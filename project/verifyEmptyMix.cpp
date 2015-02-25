#include "verifyEmptyMix.h"

verifyEmptyMix::verifyEmptyMix(){

}

void verifyEmptyMix::check(std::string check ,metsparserContext& context){

	if ( check.compare("1")!=0 ) return; 
	init (context);

	if ( context.MixContainer.size() == 0 ) return;

	for ( std::map<std::string,std::string>::iterator it = context.MixContainer.begin(); it != context.MixContainer.end(); it++ ){

		hError -> getError(cat_emptymix,"METS","mix:mix empty",it->first + " empty Tag",context.metsfile,it->first);
		
	} 

}
