#include "verifyblockstructure.h"
#include "errorhandler.h"
#include <vector>
#include "../common_files/utilities.h"


//!verify block structure 
verifyblockstructure::verifyblockstructure(datafactory *dfverifiers,ErrorHandler *hError,const std::string &fname)
{	
	hError->begin("Verify: block structure");
	datafactory_set<altoblock> dfaltoblock= dfverifiers->get_set<altoblock>();

	for (datafactory_set<altoblock>::iterator it = dfaltoblock.begin(); it != dfaltoblock.end(); ++it)
	{
		if (it->printSpaceVpos < 0 || it->printSpaceVpos > 10000 || it->printSpaceHpos < 0 || it->printSpaceHpos > 10000 ||
			it->printSpaceWidth< 100 || it->printSpaceWidth > 10000 || it->printSpaceHeight < 100 || it->printSpaceHeight > 10000) 
		{
			Block b; 
			b.hpos = it->printSpaceHpos; 	
			b.vpos = it->printSpaceVpos ;
			b.width = it->printSpaceWidth;
			b.height = it->printSpaceHeight;

			hError->getError(cat_strangePrintspaceNumber,"LINKEDFILES",it.key(),dump_alto_rect2str(b) ,it.key(),"Printspace");			
		}	

		for (std::map<std::string,Block>::iterator it2 = it->mapalto.begin(); it2 != it->mapalto.end(); ++it2)
		{			
			if (it2->second.height <= 0 || it2->second.width <= 0 )
			{
				hError->getError(cat_emptyBlock,"LINKEDFILES",it.key(), it2->first + " " + dump_alto_rect2str(it2->second),it.key(),it2->first);			

			}
			else if 
				(it2->second.vpos < it->printSpaceVpos ||
				it2->second.vpos > it->printSpaceVpos + it->printSpaceHeight ||
				it2->second.hpos < it->printSpaceHpos ||
				it2->second.hpos > it->printSpaceHpos + it->printSpaceWidth ||
				it2->second.vpos + it2->second.height > it->printSpaceVpos + it->printSpaceHeight ||
				it2->second.hpos + it2->second.width > it->printSpaceHpos + it->printSpaceWidth ||
				it2->second.width < 1 ||
				it2->second.height < 1) 			
			{
				if (it2->second.vpos < 0 || it2->second.vpos > 10000 || it2->second.width > 10000 || it2->second.width < 0) 
				{					
					hError->getError(cat_incorrectBlock,"LINKEDFILES",it.key(), dump_alto_rect2str(it2->second),it.key(),it2->first);			
				}
				else 
				{						
					hError->getError(cat_BlockOutsidePrintspace,"LINKEDFILES",it.key(), dump_alto_rect2str(it2->second),it.key(),it2->first);			
				}
			}
		}
	}
}


