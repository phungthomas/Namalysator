#include "verifyimg.h"
#include "errorhandler.h"
#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

//verify if the image file exist
verifyimg::verifyimg(datafactory *dfverifiers,errorHandler *hError,std::string &pathdirectory)
{

	File_Group *fg = dfverifiers->get<File_Group>("IMGGRP");
	bool err_found = false;	

	if ( fg != NULL ) {
		for (size_t i=0;i < fg->vect.size();i++)
		{
			Type_File tf = fg->vect[i];
			std::string fname = pathdirectory + tf.ref;	
			if (atoi(fname.substr(fname.length() - 9, 5).c_str()) != tf.seq)
			{
				char tmp[20];
				sprintf_s(tmp, "%05d", tf.seq);			
				hError->getError(cat_sequenceIncorrect,"METS","FILESEC",tf.ref +" should end in " + std::string(tmp),fname,tf.ref);		
			}
			FILE *fp ;
			fopen_s(&fp,fname.c_str(), "r");
			if (!fp)
			{
				std::cout << "File does not exist :" << fname << endl;
				hError->getError(cat_missingFile,"METS","FILESEC",tf.id +" does not exist ",fname,"");		
			} 
			else 
			{
				fclose(fp);
			}
		}
	}
}