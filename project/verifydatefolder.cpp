#include "verifydatefolder.h"
#include "../common_files/utilities.h"
#include <iostream>

//! Verify if name(date) of folder equals name(date) of Metsfile
verifydatefolder::verifydatefolder(ErrorHandler *hError,std::string &currentMetsFile, std::string &currentMetsPath)
{
	hError->begin("Verify: date of folder");
	if (currentMetsFile.substr(0,13)!=currentMetsPath.substr(currentMetsPath.length()-13,currentMetsPath.length()))
	{			
		hError->getError(cat_wrongFolderName,"METS","FOLDER", "Name of Metsfile : " + currentMetsFile.substr(0,13) + " != Name of folder :" + currentMetsPath.substr(currentMetsPath.length()-13,currentMetsPath.length()) ,currentMetsFile,"");	
	
	}
}