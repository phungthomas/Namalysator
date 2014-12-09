#include "verifyidentifierinmix.h"
#include "errorhandler.h"
#include <vector>
#include <iostream>

//Data integrity : verify administrative metadata ID from logical structure
verifyidentifierinmix::verifyidentifierinmix(datafactory *dfverifiers,errorHandler *hError,std::string &fileName)
{	
	File_Group *fg = 0;
	fg = dfverifiers->get<File_Group>("IMGGRP");
	for(size_t j=0;j< fg->vect.size();j++)
	{			
		AmdSec *amdsec = dfverifiers->get<AmdSec>(fg->vect[j].admid);
		if (amdsec ==0)
		{					
			hError->getError(cat_amdsecID,"METS","MIX",fg->vect[j].admid,fileName,"<amdsec");					
		}
	}
}
