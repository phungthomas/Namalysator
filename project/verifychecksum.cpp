#include "verifychecksum.h"
#include "md5wrapper.h"

verifychecksum::verifychecksum(datafactory *dfverifiers,errorHandler *hError,const std::string &fileName,const std::string &path)
{
	hError->begin("Verify: checksum");
	datafactory_set<File_Group> dftypefile = dfverifiers->get_set<File_Group>();		
	md5wrapper md5;	// by default md5 
	md5wrapper sha512; // only if type is SHA512

	for (datafactory_set<File_Group>::iterator it = dftypefile.begin(); it != dftypefile.end(); ++it)
	{	
		for (size_t i =0;i< it->vect.size();i++)
		{
			Type_File tf = it->vect[i];
			std::string filePath = path + it->vect[i].ref;
			if ( tf.checksumtype.compare("SHA512") ){
				if (strcmp(tf.checksum.c_str(),sha512.getHashFromFile(filePath).c_str())!=0 )
				{			
					hError->getError(cat_wrongChecksum,"METS","FileGrp","SHA512 checksum of " + tf.id + " is " + md5.getHashFromFile(filePath),fileName,tf.checksum);
				}
			} else {
				if (strcmp(tf.checksum.c_str(),md5.getHashFromFile(filePath).c_str())!=0 )
				{			
					hError->getError(cat_wrongChecksum,"METS","FileGrp","MD5 checksum of " + tf.id + " is " + md5.getHashFromFile(filePath),fileName,tf.checksum);
				}
			}
		}
	}
}
