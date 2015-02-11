#include "structgui.h"
#include "dbrequest.h"
#include <sstream>
#include <direct.h> // for getcwd
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"

#include "boost/progress.hpp"
namespace fs = boost::filesystem;

// class BatchDetail

MetsFile *BatchDetail::getMetsByID(int id)
{
	MetsFile *tmp = new MetsFile;
	dbrequest db;
	db.setDataBaseName(database);
	*tmp = db.getMets(id);
	if (tmp->idMets == 0) {
		delete tmp;
		return 0;
	} else {
		return tmp;
	}
}

BatchDetail BatchDetail::bd ;


std::string BatchDetail::getErrorPath(){
	    //get current path of the folder
		fs::path CurrentPath( fs::initial_path<fs::path>());
		
		std::stringstream errorImgPath;	
		std::size_t pos = database.find_last_of("/");
		errorImgPath << CurrentPath << "/ErrorImg_"<< database.substr(pos+1) ; 	
		_mkdir(errorImgPath.str().c_str());
		return errorImgPath.str();
}

bool BatchDetail::getMetsByID(int id, MetsFile &result)
{
	dbrequest db;
	db.setDataBaseName(database);
	result = db.getMets(id);
	return (result.idMets != 0);
}

std::vector<MetsFile> *BatchDetail::getMetsByDate(QDate date)
{
	dbrequest db;
	db.setDataBaseName(database);
	return db.getMetsByDate(idTestSet, date);
}

bool BatchDetail::getMetsByDate(QDate date, std::vector<MetsFile> &result)
{
	dbrequest db;
	db.setDataBaseName(database);
	std::vector<MetsFile> *res = db.getMetsByDate(idTestSet, date);
	if (res) {
		result = *res;
		delete res;
		return true;
	} else {
		return false;
	}
}