#ifndef EXPORTDATA_H_
#define EXPORTDATA_H_

#include "structgui.h"
#include "dbrequest.h"
#include "odswriter.h"
#include "structgui.h"
#include <sstream>
class exportdata
{
private:	
	sqlite3 *db;	
	
public:
	exportdata();
	void exportDates(odswriter *ow, BatchDetail *bddetail,dbrequest *db);
	void writeToExcel(BatchDetail detail);
	void writeSummary(odswriter *ow, BatchDetail *bddetail,dbrequest *db);
	void writeCatError(odswriter *ow, BatchDetail *bdetail,dbrequest *db);
	void exportIssues(std::map<int,MetsFile> mapMets,std::string fileName);
	void exportErrors(BatchDetail batchdetail,std::string fileName);
};





#endif // EXPORTDATA_H_