#ifndef ErrorHandler_H_
#define ErrorHandler_H_

#include <string>
#include "../common_files/struct.h"
#include "sql.h"
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>

//! handle errors encountered
class errorHandler : public xercesc::ErrorHandler
{
private:
	std::string logFilePath;		
	database *db;
	std::string _relatedType;
	std::string _file_part;
public:
	enum severity {s_warning, s_error, s_fatal};

	errorHandler(){};
	virtual ~errorHandler(){};

	void setDatabase(database *db);
	inline database * getDatabase (){ return db;}; // not nice shortcut
	void writeToLog(errorType category,const std::string &fileName,const std::string &message);
	//void getMetsError(errorType category,const std::string &relatedType,const std::string &file_part,Error error,const std::string &fname );
	void begin(const std::string &info);
	void getDateError(errorType category,std::string dateBegin,std::string dateEnd,std::string issues,std::string comment);
	void setlogFilePath(const std::string &pathLog);
	void getError(errorType category,const std::string &relatedType,const std::string &file_part, const std::string &message,const std::string &fName, std::string id);

    virtual void warning (const xercesc::SAXParseException&);
    virtual void error (const xercesc::SAXParseException&);
    virtual void fatalError (const xercesc::SAXParseException&);
    virtual void resetErrors () { /* failed_ = false; */ };
    void handle (const xercesc::SAXParseException&, severity);

	void setRelatedType(std::string rel){_relatedType=rel;};
	void setFilePart(std::string filepart){std::string _file_part=filepart;};
	

};


#endif	//ErrorHandler_H_