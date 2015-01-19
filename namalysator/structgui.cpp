#include "structgui.h"
#include "dbrequest.h"

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