#include "errorhandler.h"
#include <sstream>
#include <iostream>

void ErrorHandler::setDatabase(database *database)
{
	db = database;
}
std::string convertStringErrorMessage(const Error &error)
{
	std::ostringstream os;
	
	os << " -> line :" << error.errorline << " column :" << error.errorcolumn
                  << (error.severity == 1
                      ? " error: "
                      : " warning: ") << error.message;
	return os.str();
}

//! write message to log file
//! \param catagory error category
//! \param fileName name of the current Mets
//! \param message the string to write in the log
void ErrorHandler::writeToLog(int category,const std::string &fileName, const std::string &mess)
{	
	ErrorTypeMets error =  db->getErrorTypeWithId(category);
	std::string message = "ERROR: "  + error.error + ": " + mess;
		
	FILE *fp;
	fopen_s(&fp,logFilePath.c_str(), "a");
	if (fp!=NULL)
	{
		fprintf(fp,"%s\n", message.c_str());
		fclose(fp);
	}
	else
	{
		std::cout << "could not write to log --> Programm will continue " << std::endl; 	
	}
}
//! get error from Mets during parsing files
void ErrorHandler::getMetsError(int category,const std::string &relatedType,const std::string &file_part,Error e,const std::string &fName)
{		
	writeToLog(category,fName,convertStringErrorMessage(e));	
	db->insertMetsError(category,relatedType,file_part,e);
}

//! write to log where the parser currently is
void ErrorHandler::begin(const std::string &info)
{
	FILE *fp;
	fopen_s(&fp,logFilePath.c_str(), "a");
	if (fp!=NULL)
	{
		fprintf(fp,"%s\n", info.c_str());
		fclose(fp);
	}
	else
	{
		std::cout << "could not write to log --> Programm will continue " << std::endl; 	
	}
}
//! set path of log
void ErrorHandler::setlogFilePath(const std::string &pathLog)
{
	logFilePath = pathLog;
}

//! function called when a date error found
void ErrorHandler::getDateError(int category,std::string dateBegin,std::string dateEnd,std::string issues,std::string comment)
{
	writeToLog(category,"",comment);		
	db->insertDateError(category,dateBegin,dateEnd,issues,comment);
}

//! get Error from the verifiers
void ErrorHandler::getError(int category,const std::string &relatedType,const std::string &file_part, const std::string &message,const std::string &fName, std::string id)
{		
	writeToLog(category,fName,message);		
	Error e;
	e.errorcolumn =0;
	e.errorline =0;
	e.message = message;
	db->insertMetsErrorWithId(category,relatedType,file_part,e,id);
}	