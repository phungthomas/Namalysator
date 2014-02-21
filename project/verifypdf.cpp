#include "verifypdf.h"
#include "errorhandler.h"

verifypdf::verifypdf(datafactory *dfverifiers,ErrorHandler *hError,std::string &pathdirectory)
{	
	File_Group *fg = dfverifiers->get<File_Group>("PDFGRP");	
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
			hError->getError(cat_missingFile,"METS","FILESEC",tf.id +" does not exist ",fname,"");					
		} 
		else 
		{
			fclose(fp);
		}
	}
}