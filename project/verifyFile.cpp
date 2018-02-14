#include <iostream>
#include "verifyFile.h"
#include "errorhandler.h"


verifyFile::verifyFile(datafactory *dfverifiers,errorHandler *hError,std::string &pathdirectory,std::string TYPE,bool skipNamingTest)
{	
	File_Group *fg = dfverifiers->get<File_Group>(TYPE.c_str());
	if ( fg != NULL ) {
		for (size_t i=0;i < fg->vect.size();i++)
		{
			Type_File tf = fg->vect[i];
			std::string fname = pathdirectory + tf.ref;
			// The SEQ attribute is only present for the IMGGRP
			// For the other groups, we have to check it indirectly, through 
			// 1. get GROUPID
			// 2. find image with same GROUPID
			// 3. get the SEQ value from that image
			if (skipNamingTest){
				if (atoi(fname.substr(fname.length() - 9, 5).c_str()) != tf.seq)
				{
					char tmp[20];
					sprintf_s(tmp, "%05d", tf.seq);					
					hError->getError(cat_sequenceIncorrect,"METS","FILESEC",tf.ref +" should end in " + std::string(tmp)/*+" "+fname*/,fname,tf.ref);
					//std::cout<<"DEBUG"<<fname.substr(fname.length() - 9, 5)<<std::endl;
				}
			}
			FILE *fp ;
			fopen_s(&fp,fname.c_str(), "r");
			if (!fp)
			{			
				hError->getError(cat_missingFile,"METS","FILESEC",tf.id +" does not exist ",fname,"");					
			} 
			else 
			{
				fclose(fp);
			}
		}
	}else {
		hError->getError(cat_nongrpDefine,"METS","FILESEC","Error: No "+TYPE,pathdirectory,"");
	}
}
