#include "verifyEmptyMix.h"

verifyEmptyMix::verifyEmptyMix(){

}

void verifyEmptyMix::check(int check ,metsparserContext& context){

	if ( check!=1 ) return; 
	init (context);

	if ( context.MixContainer.size() == 0 && context.MixContainerNotDefine.size() == 0 ) return;

	for ( std::map<std::string,std::string>::iterator it = context.MixContainer.begin(); it != context.MixContainer.end(); it++ ){

		hError -> getError(cat_emptymix,"METS","mix:mix empty",it->first + " empty Tag",context.currentMetsFile,it->first);
		
	} 

	for ( std::map<std::string,std::string>::iterator it = context.MixContainerNotDefine.begin(); it != context.MixContainerNotDefine.end(); it++ ){

		hError -> getError(cat_emptymix,"METS","mix:mix empty",it->first + " Mandatory Tag not define",context.currentMetsFile,"");
		
	}

}
