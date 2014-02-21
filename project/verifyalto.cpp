#include "verifyalto.h"
#include <vector>
#include <iostream>

verifyalto::verifyalto(datafactory *dfverifiers,ErrorHandler *hError,std::string &pathdirectory)
{
	File_Group *fg = dfverifiers->get<File_Group>("ALTOGRP");
	File_Group *img = dfverifiers->get<File_Group>("IMGGRP");
	for (size_t i=0;i < fg->vect.size();i++)
	{
		Type_File tf = fg->vect[i];
		Type_File tfImg = img->vect[i];
		std::string fname = pathdirectory + tf.ref;

		if (fname.substr(fname.length() - 9) == "-alto.xml") // For Jouve because file ends with -alto.xml
		{		
			if (atoi(fname.substr(fname.length() - 14, 5).c_str()) != tfImg.seq)		
				{
					char tmp[20];
					sprintf_s(tmp, "%05d", tfImg.seq);
					hError->getError(cat_sequenceIncorrect,"METS","FILESEC",tf.ref +" should end in " + std::string(tmp),fname,tf.ref);		
				}
		} 
		else if (atoi(fname.substr(fname.length() - 9, 5).c_str()) != tfImg.seq)		
		{
			char tmp[20];
			sprintf_s(tmp, "%05d", tfImg.seq);		
			hError->getError(cat_sequenceIncorrect,"METS","FILESEC",tf.ref +" should end in " + std::string(tmp),fname,tf.ref);		
		}
		FILE *fp ;
		fopen_s(&fp,fname.c_str(), "r");
		if (!fp) 
		{	
			hError->getError(cat_missingFile,"METS","FILESEC",tf.ref +" does not exist ",tf.ref,tf.ref);
		} 
		else
		{
			fclose(fp);
		}
	}
}