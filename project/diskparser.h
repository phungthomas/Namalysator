#ifndef DISKPARSER_H_
#define DISKPARSER_H_

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"
#include "errorhandler.h"
#include <vector>

namespace fs = boost::filesystem;

//!Parse the disk and get all the Mets files.
class DiskParser 
{
private:
	ErrorHandler *hError;	
	std::vector<std::pair<std::string, std::string>> vectMets;		
public:	
	//!Constructor
	DiskParser(ErrorHandler *hError);
	//! Parse the disk and get all the Mets files. 
	/*!
      \param path root path of the folder     
      \return a vector<pair<string,string> > with the first argument the name of the METS, and the second argument the path of the METS 
    */
	std::vector<std::pair<std::string, std::string> > parseDisk(std::string &path);	
//! Verify if the file is a METS or not
	/*!
	\param fName a string argument
	\return TRUE if a match was found, FALSE otherwise.
	*/	
	bool isMets(const std::string &fname);
	
//! Recursive function that parse all the folder on the disk
	/*!
      \param full_path path of the current element found on the disk     
    */
	void parseDirectory(fs::path full_path);

};
#endif	//DISKPARSER_H_
