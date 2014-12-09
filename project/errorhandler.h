#ifndef ErrorHandler_H_
#define ErrorHandler_H_

#include <string>
#include "../common_files/struct.h"
#include "sql.h"

//! handle errors encountered
class errorHandler
{
private:
	std::string logFilePath;		
	database *db;

public:	
	void setDatabase(database *db);
	void writeToLog(int category,const std::string &fileName,const std::string &message);
	void getMetsError(int category,const std::string &relatedType,const std::string &file_part,Error error,const std::string &fname );
	void begin(const std::string &info);
	void getDateError(int category,std::string dateBegin,std::string dateEnd,std::string issues,std::string comment);
	void setlogFilePath(const std::string &pathLog);
	void getError(int category,const std::string &relatedType,const std::string &file_part, const std::string &message,const std::string &fName, std::string id);
};


#endif	//ErrorHandler_H_