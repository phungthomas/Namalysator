#include "verifydatefolder.h"
#include "../common_files/utilities.h"
#include <iostream>

//! Verify if name(date) of folder equals name(date) of Metsfile
verifydatefolder::verifydatefolder(errorHandler *hError,std::string &currentMetsFile, std::string &currentMetsPath)
{
	hError->begin("Verify: date of folder");
	const int min = 13;
	if ( min <= currentMetsPath.length() ) {
		if (currentMetsFile.substr(0,13)!=currentMetsPath.substr(currentMetsPath.length()-min,currentMetsPath.length()))
		{			
			hError->getError(cat_wrongFolderName,"METS","FOLDER", "Wrong naming. Mets file '" + currentMetsFile.substr(0,13) + " and folder '" + currentMetsPath.substr(currentMetsPath.length()-min,currentMetsPath.length())+"'" ,currentMetsFile,"");		
		}
	}else{
			hError->getError(cat_wrongFolderName,"METS","FOLDER", "Wrong naming(bad length). Mets file '" + currentMetsFile.substr(0,13) + " and folder '" + currentMetsPath.substr(0,currentMetsPath.length())+"'"  ,currentMetsFile,"");			
	}
}