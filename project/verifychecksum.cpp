#include "verifychecksum.h"
#include "md5wrapper.h"
#include "sha512wrapper.h"
#include <iostream>

verifychecksum::verifychecksum(datafactory *dfverifiers,errorHandler *hError,const std::string &fileName,const std::string &path)
{
	hError->begin("Verify: checksum");
	datafactory_set<File_Group> dftypefile = dfverifiers->get_set<File_Group>();		
	md5wrapper md5;	// by default md5 
	 // only if type is SHA512

	for (datafactory_set<File_Group>::iterator it = dftypefile.begin(); it != dftypefile.end(); ++it)
	{	
		for (size_t i =0;i< it->vect.size();i++)
		{
			Type_File tf = it->vect[i];
			std::string filePath = path + it->vect[i].ref;
			
			if ( tf.checksumtype.compare("SHA-512") == 0 ){
				
				sha512wrapper sha512;
				std::string hashcode = sha512.getHashFromFile(filePath);
				//std::cerr << filePath << ":" << hashcode <<std::endl;
				if (strcmp(tf.checksum.c_str(),hashcode.c_str())!=0 )
				{			
					hError->getError(cat_wrongChecksum,"METS","FileGrp","SHA-512 checksum of " + tf.id + " is " + hashcode,fileName,tf.checksum);
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
