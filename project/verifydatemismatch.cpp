#include "verifydatemismatch.h"
#include <string>
#include <iostream>
#include "sql.h"
#include "../common_files/struct.h"


verifydatemismatch::verifydatemismatch(errorHandler *hError,Mets *mets)
{
	hError->begin("Verify: date of issue equals date");
	if (strcmp(mets->fileName.substr(0,10).c_str(),mets->date.c_str()) !=0)
	{	
		hError->getError(cat_dateMisMatch,"METS","FOLDER", "Date missmatch -  date of directory  : " + mets->fileName.substr(0,10) + " - Date issue: " + mets->date,mets->fileName,"");
	}
}
