#include "verifymeasurement.h"

verifyMeasurement::verifyMeasurement(datafactory *dfverifiers,errorHandler *hError,std::string &fname){

	hError->begin("Verify: Measurement mm10");
	datafactory_set<altoblock> dfaltoblock= dfverifiers->get_set<altoblock>();
	for (datafactory_set<altoblock>::iterator it = dfaltoblock.begin(); it != dfaltoblock.end(); ++it)
	{	
		static const std::string measureSTD="mm10";
		if (it->measurement != measureSTD)
		{
			hError->getError(cat_measurement,"ALTOFILE Measurement",it.key(),it.key() ,it.key(),it->measurement);			
		}	
	}

}