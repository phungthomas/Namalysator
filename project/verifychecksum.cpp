#include "verifychecksum.h"
#include "md5wrapper.h"

verifychecksum::verifychecksum(datafactory *dfverifiers,ErrorHandler *hError,const std::string &fileName,const std::string &path)
{
	hError->begin("Verify: checksum");
	datafactory_set<File_Group> dftypefile = dfverifiers->get_set<File_Group>();		
	md5wrapper md5;	
	for (datafactory_set<File_Group>::iterator it = dftypefile.begin(); it != dftypefile.end(); ++it)
	{	
		for (size_t i =0;i< it->vect.size();i++)
		{
			Type_File tf = it->vect[i];
			std::string filePath = path + it->vect[i].ref;				
			if (strcmp(tf.checksum.c_str(),md5.getHashFromFile(filePath).c_str())!=0 )
			{			
				hError->getError(cat_wrongChecksum,"METS","FileGrp","checksum of " + tf.id + " is " + md5.getHashFromFile(filePath),fileName,tf.checksum);
			}
		}
	}
}
