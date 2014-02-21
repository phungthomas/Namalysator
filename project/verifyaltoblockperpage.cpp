#include "verifyaltoblockperpage.h"


verifyaltoblockperpage::verifyaltoblockperpage(datafactory *dfverifiers,ErrorHandler *hError,std::string &fname)
{	
	hError->begin("Verify: alto block per page");
	bool supplement= false;
	datafactory_set<dmdsec> dfissue = dfverifiers->get_set<dmdsec>();
	for (datafactory_set<dmdsec>::iterator it = dfissue.begin(); it != dfissue.end(); ++it)
	{		
		if (it.key().find("MODSMD_SUPPLEMENT")!=string::npos)
		{	
			supplement = true;	
			break;		
		}
	}	
	datafactory_set<altoblock> dfaltoblock= dfverifiers->get_set<altoblock>();
	for (datafactory_set<altoblock>::iterator it = dfaltoblock.begin(); it != dfaltoblock.end(); ++it)
	{	
		if (it->mapalto.size() <=1 && supplement == false)
		{
			hError->getError(cat_altoPerPage,"LINKEDFILES",it.key(),it.key() ,it.key(),"");			
		}	
	}
}