#include "dbrequest.h"
#include <sstream>
#include <iomanip>
#include "gui_utilities.h"
#include <QDate>
#include <QTime>

#ifdef LOG_TIMING
#define DEBUG_ME	{ fprintf(conn.fpLog, "SQL: %s\n\t%s\n", selectSql.c_str(), qPrintable(QTime::currentTime().toString("hh:mm:ss:zzz"))); fflush(conn.fpLog); }
#else
#define DEBUG_ME
#endif

ConnectionPool g_pool;

/////////////////////////////////////////////////////////////
// class ConnectionDB

ConnectionDB::ConnectionDB() 
{ 
	db = 0;
#ifdef LOG_TIMING
	fpLog = 0;
#endif
	reference_count = new int;
	*reference_count = 1;
}

ConnectionDB::ConnectionDB(const ConnectionDB &src)
{
	db = src.db;
#ifdef LOG_TIMING
	fpLog = src.fpLog;
#endif
	if (src.reference_count) {
		reference_count = src.reference_count;
		add_reference();
	}
}

ConnectionDB &ConnectionDB::operator=(const ConnectionDB &src)
{
	if (this != &src) { // Are we different instance of the class
		if (src.reference_count != reference_count) { // Are we pointing to different data
			del_reference();
			db = src.db;
#ifdef LOG_TIMING
			fpLog = src.fpLog;
#endif
			reference_count = src.reference_count;
			add_reference();
		}
	}
	return *this;
}

ConnectionDB::~ConnectionDB() 
{
	del_reference();
}

bool ConnectionDB::openConnection(const std::string &dbname)
{
	if (db) {
		del_reference();
	}
	int	rc = sqlite3_open(dbname.c_str(), &db);
	if (rc)	{			
		sqlite3_close(db);
		return false;
	}
#ifdef LOG_TIMING
	fpLog = fopen("C:\\Development\\sqlite-shell\\logging.txt", "a");
#endif
	add_reference();
	return true;
}

void ConnectionDB::close()
{
	if (db) {
		sqlite3_close(db);
		db = 0;
	}
#ifdef LOG_TIMING
	if (fpLog) {
		fclose(fpLog);
		fpLog = 0;
	}
#endif
}

void ConnectionDB::add_reference()
{
	(*reference_count)++;
}

void ConnectionDB::del_reference()
{
	if ((*reference_count) > 1) {
		(*reference_count)--;
	} else {
		(*reference_count) = 0;
		close();
	}
}

/////////////////////////////////////////////////////////////
// class ConnectionPool

ConnectionDB ConnectionPool::getConnection(const std::string &dbname)
{
	std::map<std::string, ConnectionDB>::iterator it = Databases.find(dbname);
	if (it != Databases.end()) {
		return it->second;
	} else {
		ConnectionDB db;
		db.openConnection(dbname);
		Databases[dbname] = db;
		return db;
	}
}

/////////////////////////////////////////////////////////////
// class dbrequest


void dbrequest::setDataBaseName(std::string dbName)
{
	databaseName = dbName;
}

// get all testsets from database
std::vector<std::string> dbrequest::getvTestSet()
{
	std::vector<std::string> vect;
	ConnectionDB conn = g_pool.getConnection(databaseName);
	sqlite3_stmt *pStmt;
	int rc;	
	const char *zErrMsg= 0; 

	std::string selectSql = "SELECT distinct (BATCHNAME) FROM TESTSET";
	DEBUG_ME
	rc = sqlite3_prepare_v2(conn.db, selectSql.c_str(), -1, &pStmt,&zErrMsg);

	if(rc == SQLITE_OK)
	{		
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			vect.push_back((const char *)sqlite3_column_text(pStmt, 0));
		}
	}
	sqlite3_finalize(pStmt);
	return vect;
}



// get all tests from Batch
std::vector<std::pair<int,std::string> > dbrequest::getvDateTestset(std::string batch)
{
	std::vector<std::pair<int,std::string>> vect;
	ConnectionDB conn = g_pool.getConnection(databaseName);
    sqlite3_stmt *pStmt;	
	const char *zErrMsg= 0; 

	std::string selectSql = "SELECT ID_TESTSET,DATE FROM TESTSET where BATCHNAME =?";
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);

	if(rc == SQLITE_OK)
	{
		sqlite3_bind_text(pStmt, 1, batch.c_str(), batch.length(), SQLITE_STATIC);
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			std::pair<int,std::string> p;
			p.first = sqlite3_column_int(pStmt, 0);
			p.second = (const char *) sqlite3_column_text(pStmt, 1);
			vect.push_back(p);	
		}
	}
	sqlite3_finalize(pStmt);
	return vect;
}

BatchDetail dbrequest::getBatch(int id_testset)
{	
	BatchDetail bdetail;
	ConnectionDB conn = g_pool.getConnection(databaseName);
    sqlite3_stmt *pStmt;
	int rc;		
	const char *zErrMsg=0; 
	std::stringstream oIdTestset;
	oIdTestset << id_testset;	
	bdetail.idTestSet = id_testset;
	std::string selectSql = "select min(m.Date),max(m. Date),count(id_mets),batchname,t.date from Mets m,Testset t where t.id_testset = m.id_testset and m.id_testset ='" + oIdTestset.str() + "'";
	DEBUG_ME
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);

	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			std::pair<std::string,std::string> p;
			bdetail.minDate = (const char *)sqlite3_column_text(pStmt, 0);
			bdetail.maxDate = (const char *)sqlite3_column_text(pStmt, 1);
			bdetail.count = sqlite3_column_int(pStmt, 2);
			bdetail.batchName = (const char *)sqlite3_column_text(pStmt, 3);
			bdetail.testDate = (const char *)sqlite3_column_text(pStmt, 4);
		}
	}
	sqlite3_finalize(pStmt);
	return bdetail;
}

/// <summary>get details of a mets</summary>	
/// <param name="id_mets">id mets</param>
/// <returns>MetsFile</returns>	
MetsFile dbrequest::getMets(int id_mets)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::stringstream oid_mets;
	oid_mets << id_mets;	
	sqlite3_stmt *pStmt;
	int rc;	
	const char *zErrMsg= 0; 
	MetsFile mets;  
	std::string selectSql = "SELECT ID_METS,ID_TESTSET,PATH,FILENAME,ISSUE_NUMBER,TITLE,PAGES,DATE,YEAR,PAPERTYPE FROM METS where ID_METS =" + oid_mets.str();
	DEBUG_ME
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);

	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			mets.idMets = sqlite3_column_int(pStmt, 0);
			mets.mapLinked["IMGGRP"] = getMapLinkedFiles(mets.idMets, "IMGGRP");
			mets.mapLinked["ALTOGRP"] = getMapLinkedFiles(mets.idMets, "ALTOGRP");
			mets.mapLinked["PDFGRP"] = getMapLinkedFiles(mets.idMets, "PDFGRP");
			mets.idTestSet = sqlite3_column_int(pStmt, 1);
			mets.path = (const char *) sqlite3_column_text(pStmt, 2);
			mets.fileName = (const char *) sqlite3_column_text(pStmt, 3);
			mets.issueNumber = (const char *) sqlite3_column_text(pStmt, 4);
			mets.vectIssueNumber = getIssueNumber(mets.issueNumber);
			mets.title = (const char *) sqlite3_column_text(pStmt, 5);
			mets.pages = sqlite3_column_int(pStmt, 6);
			mets.date =  mets.date.fromString((const char *) sqlite3_column_text(pStmt, 7), "yyyy-MM-dd");
			mets.year = sqlite3_column_int(pStmt, 8);
			mets.docType = (const char *) sqlite3_column_text(pStmt, 9);
		}	  
    }
	sqlite3_finalize(pStmt);
	// Get names of supplements
	selectSql = "SELECT TITLE_SUPPLEMENT FROM SUPPLEMENTS WHERE ID_METS = " + oid_mets.str();
	DEBUG_ME
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			mets.supplements.push_back((const char *) sqlite3_column_text(pStmt, 0));
		}
	}
	sqlite3_finalize(pStmt);
	return mets;
}

/// <summary>get details of LinkedFiles</summary>	
/// <param name="id_mets">id of mets </param>
/// <param file_part="">filepart(alto,img,pdf)</param>
/// <returns>LinkedFiles</returns>	
LinkedFiles dbrequest::getLinkedFiles(int id,std::string file_part)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::stringstream oid;
	oid << id;	
	sqlite3_stmt *pStmt;
	const char *zErrMsg= 0; 
	LinkedFiles lf;  
	std::string selectSql = "SELECT * FROM LINKEDFILES where ID_METS ='" + oid.str() + "'and FILEID = '"+ file_part + "' ";
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	if(rc == SQLITE_OK)
	{	  
      while(sqlite3_step(pStmt) == SQLITE_ROW)
      {
		int count = sqlite3_data_count(pStmt);		
		 for (int i =0;i<  count ;i++)
		 {
			const char *result = (const char *)sqlite3_column_text(pStmt, i);			
			if (i==0) lf.id = atoi(result);									
			else if (i==1) lf.idMets = atoi(result);
			else if (i==2) lf.type = atoi(result);
			else if (i==3) lf.grouId = result;
			else if (i==4) lf.checksum = result;
			else if (i==5) lf.size =  atof(result) ;
			else if (i==6) lf.fileName = result;
			else if (i==7) lf.fileId = result;		
		 }		 
	  }
   }
	sqlite3_finalize(pStmt);
   return lf;
}


// return the parameters of verified tests
Parameters dbrequest::getParameterVerifiers(int id_testset)
{
	std::stringstream oId;
	ConnectionDB conn = g_pool.getConnection(databaseName);
	oId << id_testset;	
	sqlite3_stmt *pStmt;
	const char *zErrMsg= 0; 
	Parameters param;
	
	std::string sql = "select FILECHECK,CHECKSUM,DIVS,UNLINKEDIDENTIFIER, \
	IDENTIFIERMIX,INVALIDSUPPLEMENT,NOISSUEDEFINED,ALTOBLOCKPERPAGE, \
	BLOCKSTRUCTURE,COVERAGEPERCENTALTO,MULTIBLOCKUSE,DATES,SCHEMACHECK from VERIFIERS where ID_TESTSET ='" + oId.str() + "'";
	int rc = sqlite3_prepare_v2(conn.db,sql.c_str(),-1, &pStmt,&zErrMsg);

	if(rc == SQLITE_OK)
	{	  
      while(sqlite3_step(pStmt) == SQLITE_ROW)
      {
		int count = sqlite3_data_count(pStmt);
		std::pair<int,DateError> p;
		 for (int i =0;i<  count ;i++)
		 {
			const char *result = (const char *)sqlite3_column_text(pStmt, i);
			
			if (i==0) param.checkFile = result;								
			else if (i==1) 	param.checkSum = result;	
			else if (i==2) param.divs = result;
			else if (i==3) param.unlinkedIdentifier = result;
			else if (i==4) param.identifierMix = result;		
			else if (i==5) param.invalidSupplement = result;	
			else if (i==6) param.noIssueDefined = result;		
			else if (i==7) param.altoblockPerPage = result;
			else if (i==8) param.blockStructure = result;	
			else if (i==9) param.coveragePercentAlto = result;		
			else if (i==10) param.multipleBlockUse = result;
			else if (i==11) param.dates = result;
			else if (i==12) param.schemaValidation = result;					
		 }			
	  }
    }
	sqlite3_finalize(pStmt);
	return param;  	
}

/// <summary>getTestset id's of selected batch</summary>
/// <param name="id">batchName</param>
/// <returns>vector of testset id's</returns>
std::vector<int> dbrequest::getIdTestset(std::string batchName)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::vector<int> v;
    sqlite3_stmt *pStmt;
	int rc;	
	const char *zErrMsg= 0; 		
	std::string selectSql = "select ID_TESTSET from Testset where BATCHNAME = '" + batchName + "'";
	DEBUG_ME
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			const char *result = (const char *)sqlite3_column_text(pStmt, 0);			
			v.push_back(atoi(result));
		}		 
	} 
	sqlite3_finalize(pStmt);
	return v;
}

/// <summary>get all errors of the current testset (without dates) </summary>
/// <param name="id">id_testset</param>
/// <returns>vector of ErrorSummary</returns>
std::vector<ErrorSummary> dbrequest::getvErrorSummary(int id_testset)
{
	std::vector<ErrorSummary> v ;
	ConnectionDB conn = g_pool.getConnection(databaseName);
	ErrorSummary es;
	sqlite3_stmt *pStmt;
	const char *zErrMsg= 0;
	std::stringstream sId_testset;	
	sId_testset << id_testset; 	

    std::string selectSql ="SELECT ID_ERRORTYPE,COUNT (ID_ERRORTYPE) FROM MetsError where ID_TESTSET = '" + sId_testset.str() + "' GROUP BY ID_ERRORTYPE";
	DEBUG_ME
    int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
    if(rc == SQLITE_OK)
    {	 
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			int count = sqlite3_data_count(pStmt);		
			for (int i =0;i<  count ;i++)
			{
				const char *result = (const char *)sqlite3_column_text(pStmt, i);			
				if (i==0) es.errorType = getErrorTypeWithId(atoi(result));						
				else if (i==1) es.count = atoi(result);					
			}		
			 v.push_back(es);		 
		}
	}
	sqlite3_finalize(pStmt);
	return v;
}

/// <summary>get the summary of the date errors of the current testset</summary>
/// <param name="id">id_testset</param>
/// <returns>vector of ErrorSummary</returns>
std::vector<ErrorSummary> dbrequest::getvErrorDate(int id_testset)
{
	std::vector<ErrorSummary> v ;
	ConnectionDB conn = g_pool.getConnection(databaseName);
	ErrorSummary es;
	sqlite3_stmt *pStmt;
	const char *zErrMsg= 0;
	std::stringstream sId_testset;	
	sId_testset << id_testset; 
	std::string selectSql ="SELECT ID_ERRORTYPE,COUNT (ID_ERRORTYPE) FROM DATEERROR where ID_TESTSET = '" + sId_testset.str() + "' GROUP BY ID_ERRORTYPE";
	DEBUG_ME
    int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);

    if(rc == SQLITE_OK)
    {	 
      while(sqlite3_step(pStmt) == SQLITE_ROW)
      {
		int count = sqlite3_data_count(pStmt);
		
		 for (int i =0;i<  count ;i++)
		 {
			const char *result = (const char *)sqlite3_column_text(pStmt, i);			
			if (i==0) es.errorType = getErrorTypeWithId(atoi(result));							
			else if (i==1) es.count = atoi(result);					
		 }		
		 v.push_back(es);		 
	  }
   }
	sqlite3_finalize(pStmt);
	return v;
}

/// <summary>get Errortype of the current id </summary>
/// <param name="id">id of type of error</param>
/// <returns>ErrorType</returns>
ErrorType dbrequest::getErrorTypeWithId(int id)
{
	sqlite3_stmt *pStmt;
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::stringstream ss;
	ss << id;
	int rc;	
	const char *zErrMsg= ""; 
	std::string selectSql = "SELECT * FROM ERRORTYPE where id_type ='" + ss.str()+ "'"; 
	DEBUG_ME
	std::vector<ErrorType> v;
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	ErrorType et;  
	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			
			int count = sqlite3_data_count(pStmt);		
			for (int i =0;i<  count ;i++)
			{
				const char *result = (const char *)sqlite3_column_text(pStmt, i);			
				if (i==0) et.id = atoi(result);		
				else if (i==1) et.id_type = atoi(result);					
				else if (i==2) et.error = result;
				else if (i==3) et.details = result;
				else if (i==4) et.severity = getErrorSeverityWithId(atoi(result));	
				else if (i==5) et.category = getErrorCategoryWithId(atoi(result));				
			}					 
		}		
    }
	sqlite3_finalize(pStmt);
	return et;
}

/// <summary>get ErrorSeverity of the current id of ErrorType </summary>
/// <param name="id">id of Errortype</param>
/// <returns>ErrorSeverity</returns>
ErrorSeverity dbrequest::getErrorSeverityWithId(int id)
{
	sqlite3_stmt *pStmt;
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::stringstream ss;
	ss<<id;
	int rc;	
	const char *zErrMsg= 0; 
	std::string selectSql = "SELECT * FROM ErrorSeverity where ID_SEVERITY ='" + ss.str()+ "'"; 	
	DEBUG_ME
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	ErrorSeverity es;  
	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			
			int count = sqlite3_data_count(pStmt);		
			for (int i =0;i<  count ;i++)
			{
				const char *result = (const char *)sqlite3_column_text(pStmt, i);			
				if (i==0) es.id = atoi(result);							
				else if (i==1) es.id_sevrity =atoi(result);
				else if (i==2) es.gravity = result;							
			}					 
		}		
    }
	sqlite3_finalize(pStmt);
	return es;
}

/// <summary>get ErrorCategory of the current id of ErrorType </summary>
/// <param name="id">id of Errortype</param>
/// <returns>ErrorCategory</returns>
ErrorCategory dbrequest::getErrorCategoryWithId(int id)
{	
	sqlite3_stmt *pStmt;
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::stringstream ss;
	ss<<id;
	int rc;	
	const char *zErrMsg= 0; 
	std::string selectSql = "SELECT * FROM ErrorCategory where ID_CATEGORY ='" + ss.str()+ "'"; 	
	DEBUG_ME
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	ErrorCategory ec;  
	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{			
			int count = sqlite3_data_count(pStmt);		
			for (int i =0;i<  count ;i++)
			{
				const char *result = (const char *)sqlite3_column_text(pStmt, i);			
				if (i==0) ec.id = atoi(result);							
				else if (i==1) ec.id_category =atoi(result);
				else if (i==2) ec.name = result;							
			}					 
		}		
	}
	sqlite3_finalize(pStmt);
	return ec;
}

/// <summary>get ErrorCategory of the current id of ErrorType </summary>
/// <returns>vector of ErrorType</returns>
std::vector<ErrorType> dbrequest::getErrorType()
{
	ConnectionDB conn = g_pool.getConnection(databaseName);	
	sqlite3_stmt *pStmt;
	int rc;	
	const char *zErrMsg=0; 
	std::string selectSql = "SELECT * FROM ERRORTYPE"; 
	DEBUG_ME
	//std::string selectSql = "SELECT * FROM ERRORTYPE where ID_CATEGORY = 6"; 
	std::vector<ErrorType> v;
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	ErrorType et;  
	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			
			int count = sqlite3_data_count(pStmt);		
			for (int i =0;i<  count ;i++)
			{
				const char *result = (const char *)sqlite3_column_text(pStmt, i);			
				if (i==0) et.id = atoi(result);	
				else if (i==1) et.id_type = atoi(result);						
				else if (i==2) et.error = result;
				else if (i==3) et.details = result;
				else if (i==4) 
				{
					et.severity = getErrorSeverityWithId(atoi(result));
					et.id_severity = atoi(result);		
				}	
				else if (i==5) et.category = getErrorCategoryWithId(atoi(result));
						
			}
			v.push_back(et);				 
		}		
   }
	sqlite3_finalize(pStmt);
	return v;
}



/// <summary>count number of error for distinct errortype </summary>
/// <param name="id">id of Errortype</param>
/// <param name="id">id testset</param>
/// <returns>int count</returns>
int dbrequest::getErrorTypeCountWithTestset(int idError,int id_testset)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);	
	sqlite3_stmt *pStmt;
	std::stringstream sidError,sIdTestset;
	sidError << idError;
	sIdTestset << id_testset;
	int rc;	
	int count =0;
	const char *zErrMsg= 0; 
	std::string selectSql = "SELECT count(ID) FROM MetsError where id_errortype ='" + sidError.str()+ "' and id_testset = '"+ sIdTestset.str()+"'"; 
	DEBUG_ME
	std::vector<ErrorType> v;
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	ErrorType et;  
	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{			
			const char *result = (const char *)sqlite3_column_text(pStmt, 0);			
			count = atoi(result);	
		}		
   }
	sqlite3_finalize(pStmt);
	return count;
}

/// <summary>count number of date error </summary>
/// <param name="id">id  Errortype</param>
/// <param name="id">id testset</param>
/// <returns>int count</returns>
int dbrequest::getErrorTypeCountWithTestsetDates(int idError,int id_testset)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);	
	sqlite3_stmt *pStmt;
	std::stringstream sidError,sIdTestset;
	sidError << idError;
	sIdTestset << id_testset;
	int rc;	
	int count =0;
	const char *zErrMsg= 0; 
	std::string selectSql = "SELECT count(ID) FROM DATEERROR where id_errortype ='" + sidError.str()+ "' and id_testset = '"+ sIdTestset.str()+"'"; 
	DEBUG_ME
	std::vector<ErrorType> v;
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	ErrorType et;  
	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{			
			const char *result = (const char *)sqlite3_column_text(pStmt, 0);			
			count = atoi(result);	
		}		
	}
	sqlite3_finalize(pStmt);
	return count;
}

/// <summary>get all mets</summary>
/// <param name="id">id _testset</param>
/// <returns>map QDate,MetsFile </returns>
std::map<QDate,std::vector<int> > dbrequest::getmMetsDate(int id_testset)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::stringstream oIdTestset;
	oIdTestset << id_testset;
    sqlite3_stmt *pStmt;
	const char *zErrMsg= 0;
	std::map<QDate,std::vector<int> >  mapMetsDate;
	std::vector<int> vMets;
	std::string selectSql = "SELECT ID_METS, DATE FROM METS where ID_TESTSET ='" + oIdTestset.str() + "'";
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
   if(rc == SQLITE_OK)
   {	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			int result_id_mets = sqlite3_column_int(pStmt, 0);
			const char *result_date = (const char *) sqlite3_column_text(pStmt, 1);
		    QDate date = date.fromString(result_date, "yyyy-MM-dd");
			if (mapMetsDate.find(date) == mapMetsDate.end())
			{
				vMets.clear();
				vMets.push_back(result_id_mets);
				mapMetsDate[date] = vMets;
			}
			else
			{
				mapMetsDate[date].push_back(result_id_mets);
			}	  
		}		
	}
   sqlite3_finalize(pStmt);
   return mapMetsDate;
}

/// <summary>get linked files of an mets for the selected group</summary>
/// <param name="idMets">idMets</param>
/// <param name="fileGroup">string fileGroup</param>
/// <returns>map int,LinkedFiles </returns>
std::map<int,LinkedFiles> dbrequest::getMapLinkedFiles(int idMets,std::string fileGroup)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::map<int,LinkedFiles> altoPath;
	std::stringstream oid;
	oid << idMets;	
    sqlite3_stmt *pStmt;
	int rc;	
	const char *zErrMsg= 0; 
	int page=1;
	std::string selectSql = "SELECT ID,ID_METS,TYPE,GROUPID,CHECKSUM,SIZE,FILENAME,FILEID,DPI FROM LINKEDFILES where ID_METS ='" + oid.str() + "' and TYPE = '"+ fileGroup +"'";
	DEBUG_ME
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	LinkedFiles lf;  
	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{			
			int count = sqlite3_data_count(pStmt);		
			for (int i =0;i<  count ;i++)
			{
				const char *result = (const char *)sqlite3_column_text(pStmt, i);			
				if (i==0)lf.id = atoi(result);							
				else if (i==1) lf.idMets = atoi(result);
				else if (i==2) lf.type = (result);
				else if (i==3) lf.grouId = result;
				else if (i==4) lf.checksum = result;
				else if (i==5) lf.size =  atof(result) ;
				else if (i==6) lf.fileName = result;
				else if (i==7) lf.fileId = result;		
				else if (i==8) lf.dpi = atoi(result);	
			}	
			  altoPath[page]= lf;	
			  page++;  	 
		}		
   }
   sqlite3_finalize(pStmt);
   return altoPath;
}


/// <summary>get the total of mets per year</summary>
/// <param name="id_testset">id_testset</param>
/// <returns>map year - pair total mets,total Supplement</returns>
std::map<int,std::pair<int,int>> dbrequest::getSumMetsYear(int id_testset)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::stringstream oid;
	oid << id_testset;	
    sqlite3_stmt *pStmt;
	int rc;	
	const char *zErrMsg= 0; 
   MetsFile mets;  
   std::string selectSql = "select year,count(year) from Mets where id_testset ='" + oid.str() + "' group by year";  
   DEBUG_ME
   rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
   std::map<int,std::pair<int,int>>  mapYearCount;
   if(rc == SQLITE_OK)
   {	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{	
			int count = sqlite3_data_count(pStmt);	
			int year =0;	
			std::pair<int,int> pair;
			for (int i =0;i<  count ;i++)
			{			
				const char *result = (const char *)sqlite3_column_text(pStmt, i);
				if (result!=NULL)
				{			
					if (i==0) year = atoi(result);											
					else if (i==1)pair.first = atoi(result);
				}
			}	
			if (year!=0)
			{		
				pair.second = getSumSupplYear(id_testset,year);			
				mapYearCount[year]  = pair;
			}			
		}
   }
   sqlite3_finalize(pStmt);
   return mapYearCount;
}

/// <summary>get the total of supplements</summary>
/// <param name="id_testset">id_testset</param>
/// <param name="year">current year</param>
/// <returns>sum of supllement for the year</returns>
int dbrequest::getSumSupplYear(int id_testset,int year)
{
	int numberSuppl =0;
	std::stringstream oid,oyear;
	ConnectionDB conn = g_pool.getConnection(databaseName);
	oid << id_testset;	
	oyear << year;
	sqlite3_stmt *pStmt;
	int rc;	
	const char *zErrMsg= 0;    
	std::string selectSql = "select count(title_supplement) from Mets  where id_testset ='" + oid.str() + "'and year = '" + oyear.str() + "' and title_supplement !='' group by year";  
	DEBUG_ME
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	std::map<int,int> mapYearCount;
	if(rc == SQLITE_OK)
	{	  
      while(sqlite3_step(pStmt) == SQLITE_ROW)
      {				
		const char *result = (const char *)sqlite3_column_text(pStmt, 0);			
		numberSuppl = atoi(result);			 
	  }
   } 
	sqlite3_finalize(pStmt);
   return numberSuppl;
}

/// <summary>get comments of specific date</summary>
/// <param name="id_testset">id_testset</param>
/// <returns>map of date,DateComment </returns>
std::map<QDate,DateComment> dbrequest::getDateComment(int id_testset)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::stringstream id;
	id << id_testset;		
	std::map<QDate,DateComment>  mapComment;
    sqlite3_stmt *pStmt;
	int rc;	
	const char *zErrMsg= 0; 
    DateComment dateComment;  

   std::string selectSql = "select * from Datecomment dc, dateerror de where dc.ID_DATEERROR = de.Id and id_TESTSET='" + id.str() + "'"; 
   DEBUG_ME
   rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);

   if(rc == SQLITE_OK)
   {	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			int count = sqlite3_data_count(pStmt);		
			for (int i =0;i<  count ;i++)
			{			
				const char *result = (const char *)sqlite3_column_text(pStmt, i);								
				if (i==0) dateComment.id = atoi(result);
				else if (i==1) dateComment.id_DateError = atoi(result);
				else if (i==2) dateComment.date = dateComment.date.fromString(result,"yyyy-MM-dd");
				else if (i==3)dateComment.comment = result;		
			}		
			mapComment[dateComment.date] = dateComment;	 
	  }
   }
   sqlite3_finalize(pStmt);
   return mapComment;
}

/// <summary>get vector of date error found by mets verifier</summary>
/// <param name="id_testset">id_testset</param>
/// <returns>vector with pair id,DateError </returns>
std::vector<std::pair<int,DateError>> dbrequest::getvDateError(int id_testset)
{	
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::stringstream oIdTestset,oYear;
	oIdTestset << id_testset;	
	//oYear << year;
    sqlite3_stmt *pStmt;
	int rc;	
	const char *zErrMsg= 0; 
	DateError derror;
	std::vector<std::pair<int,DateError>>  vDateError;
	std::string selectSql = "SELECT ID,ID_TESTSET,DATE_BEGIN,DATE_END,ISSUES,COMMENT,ID_ERRORTYPE FROM DATEERROR where ID_TESTSET ='" + oIdTestset.str() + "'";
	DEBUG_ME
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);

	if(rc == SQLITE_OK)
	{	  
      while(sqlite3_step(pStmt) == SQLITE_ROW)
      {
		int count = sqlite3_data_count(pStmt);
		std::pair<int,DateError> p;
		 for (int i =0;i<  count ;i++)
		 {
			const char *result = (const char *)sqlite3_column_text(pStmt, i);
			
			if (i==0)
			{ 
				derror.id = atoi(result);
				p.first = atoi(result);
			}
							
			else if (i==1) derror.id_testset = atoi(result);
			else if (i==2) derror.dateBegin = result;
			else if (i==3) derror.dateEnd = result;
			else if (i==4)			
			{
				derror.issues = result;
			//	derror.vectIssueNumber = getIssueNumber(result);
			}
			else if (i==5) derror.comment = result;
			else if (i==6) derror.valider = result;		
			else if (i==7) derror.errorType = atoi(result);			
		 }
		 
		derror.comment = messageMisisngIssue(derror);
		 
		p.second = derror;
		 vDateError.push_back(p);
		 
	  }
   }
	sqlite3_finalize(pStmt);
   return vDateError;
}


///<summary>update comment of calendar</summary>
void dbrequest::updateDateComment(int id,std::string comment)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);
	char *zErrMsg =0;
	std::stringstream o;
	o << id;	
	std::string sql =	"UPDATE DATECOMMENT SET COMMENT ='" + comment + "' where ID = '"+ o.str() +"'";					
		
	int rc = sqlite3_exec(conn.db, sql.c_str(), NULL, 0, &zErrMsg); //null because no calll back needed
	
	if( rc )
	{
		fprintf(stderr, "Can't update data COMMENTS: %s\n",  zErrMsg);
	}
}


//! insert comment of calendar
bool dbrequest::insertComment(int id_mets,std::string date, std::string comment)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::stringstream id;
	
	id << id_mets;
	char *zErrMsg=0;
	
	std::string sql = "INSERT INTO DATECOMMENT ('ID_DATEERROR','DATE','COMMENT')  \
					  VALUES  ('" + id.str() + "','" + date + "','" + comment +"')"; 							
	
	int rc = sqlite3_exec(conn.db, sql.c_str(), NULL, 0, &zErrMsg); 	
	if( rc )
	{
		fprintf(stderr, "Can't insert data TestSet: %s\n",zErrMsg);
		return false;
	}	
	return true;
}

/// <summary>count of erros of each errotype</summary>
/// <param name="idTestset">id testset</param>
/// <param name="errortype">id errortype</param>
/// <returns>int</returns>
int dbrequest::getcountMetsErrorForEachErrorType(int idTestset,int errortype)
{
	std::vector<MetsError> v ;
	ConnectionDB conn = g_pool.getConnection(databaseName);
	MetsError es;
	sqlite3_stmt *pStmt;	
	std::stringstream sId_testset,siderror;	
	sId_testset << idTestset; 	
	siderror << errortype;		
	const char *zErrMsg= 0; 	
	set<int> pileMets;
	std::string selectSql = "select distinct (id_related) from MetsError where ID_TESTSET = '"+ sId_testset.str() + "' and id_errortype = '" +siderror.str() + "'";
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);

   if(rc == SQLITE_OK)
   {	   
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		  {
			int count = sqlite3_data_count(pStmt);	
			    
			for (int i =0;i<  count ;i++)
			{	
				const char *result = (const char *)sqlite3_column_text(pStmt, i);						
				if (pileMets.find(atoi(result)) == pileMets.end())
				{
					pileMets.insert(atoi(result));
				}
			}
		}
	} 
    sqlite3_finalize(pStmt);
	std::string selectSqlLinked = "select distinct (ID_METS) from MetsError S,LINKEDFILES l where s.ID_TESTSET ='"+ sId_testset.str() + "' and RELATED_TYPE = 'LINKEDFILES' and s.id_related = l.id and id_errortype = '" +siderror.str() + "'";
	
	 rc = sqlite3_prepare_v2(conn.db, selectSqlLinked.c_str(),-1, &pStmt,&zErrMsg);

	if(rc == SQLITE_OK)
	{	       
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		 {
			int count = sqlite3_data_count(pStmt);		    
			for (int i =0;i<  count ;i++)
			{
				const char *result = (const char *)sqlite3_column_text(pStmt, i);		
				if (pileMets.find(atoi(result)) == pileMets.end())
				{
					pileMets.insert(atoi(result));
				}
			}
		}
	}
	sqlite3_finalize(pStmt);
	return pileMets.size();
}

/// <summary>count of schema Errors except dates</summary>
/// <param name="id">id testset</param>
/// <returns>int</returns>
int dbrequest::getcountMetsError(int idTestset)
{
	std::vector<MetsError> v ;
	ConnectionDB conn = g_pool.getConnection(databaseName);
	MetsError es;
	sqlite3_stmt *pStmt;	
	std::stringstream sId_testset;	
	sId_testset << idTestset; 		
	
	const char *zErrMsg= ""; 	
	set<int> pileMets;
	std::string selectSql = "select distinct (id_related) from MetsError where ID_TESTSET = '"+ sId_testset.str() + "'";
	DEBUG_ME
	
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);

   if(rc == SQLITE_OK)
   {	   
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		  {
			int count = sqlite3_data_count(pStmt);	
			    
			for (int i =0;i<  count ;i++)
			{	
				const char *result = (const char *)sqlite3_column_text(pStmt, i);						
				if (pileMets.find(atoi(result)) == pileMets.end())
				{
					pileMets.insert(atoi(result));
				}
			}
		}
	}
   sqlite3_finalize(pStmt);
  
	std::string selectSqlLinked = "select distinct (ID_METS) from MetsError S,LINKEDFILES l where s.ID_TESTSET ='"+ sId_testset.str() + "' and RELATED_TYPE = 'LINKEDFILES' and s.id_related = l.id ";
	
	rc = sqlite3_prepare_v2(conn.db,selectSqlLinked.c_str(),-1, &pStmt,&zErrMsg);

	if(rc == SQLITE_OK)
	{	       
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		 {
			int count = sqlite3_data_count(pStmt);		    
			for (int i =0;i<  count ;i++)
			{
				const char *result = (const char *)sqlite3_column_text(pStmt, i);		
				if (pileMets.find(atoi(result)) == pileMets.end())
				{
					pileMets.insert(atoi(result));
				}
			}
		}
	}
	sqlite3_finalize(pStmt);
	return pileMets.size();
}

/// <summary>count number of titles to check </summary>
/// <param name="id">id testset</param>
/// <returns>int count</returns>
int dbrequest::getcountTitleCheck(int id_testset)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);	
	sqlite3_stmt *pStmt;
	std::stringstream sIdTestset;	
	sIdTestset << id_testset;
	int rc;	
	int count =0;
	const char *zErrMsg= 0; 
	std::string selectSql = "select count(a.id) from article a, mets m where mustcheck = 1 and a.id_mets = m.id_mets and m.id_testset = '"+ sIdTestset.str()+"'"; 
	DEBUG_ME
	std::vector<ErrorType> v;
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	ErrorType et;  
	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{			
			const char *result = (const char *)sqlite3_column_text(pStmt, 0);			
			count = atoi(result);	
		}		
    }
	sqlite3_finalize(pStmt);
	return count;
}

/// <summary>get a vector of Mets errors </summary>
/// <param name="id_cat">id category</param>
/// <param name="id_testset">id testset</param>
/// <param name="year">year</param>
/// <returns>vector of mets error</returns>
std::vector<MetsError> dbrequest::getvErrorPerCategory(int id_cat, int idTestset)
{
	std::vector<MetsError> v;
	ConnectionDB conn = g_pool.getConnection(databaseName);
	MetsError es;
	sqlite3_stmt *pStmt;	
	std::stringstream sId_testset,sidCat,sYear;	
	sId_testset << idTestset; 	
	sidCat << id_cat;	
	const char *zErrMsg= 0; 	
	std::string selectSql = "select s.ID,s.ID_RELATED,s.RELATED_TYPE,s.FILE_PART,s.ERRORLINE,s.ERRORCOLUMN,s.MESSAGE,s.ID_ERRORTYPE,s.id_search from MetsError s,ERRORTYPE e where s.ID_ERRORTYPE = e.ID_TYPE and e.ID_CATEGORY = '"+ sidCat.str() + "' and s.ID_TESTSET = '"+ sId_testset.str() + "'";
	DEBUG_ME

	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);

    if(rc == SQLITE_OK)
    {	  
      while(sqlite3_step(pStmt) == SQLITE_ROW)
      {
		int count = sqlite3_data_count(pStmt);
		
		 for (int i =0;i<  count ;i++)
		 {
			const char *result = (const char *)sqlite3_column_text(pStmt, i);
			if (i==0) es.id= atoi(result); 							
			else if (i==1) es.idRelatedFile = atoi(result);
			else if (i==2) es.relatedType = result;	
			else if (i==3) es.filePart = result;
			else if (i==4) es.errorLine = atoi(result);
			else if (i==5) es.errorColumn = atoi(result);
			else if (i==6) es.message = result;
			else if (i==7) es.errorType = getErrorTypeWithId(atoi(result));
			else if (i==8) es.id_search = result;
		 }

		 if (strcmp(es.relatedType.c_str(),"METS") == 0)
		 {
			MetsFile mets = getMets(es.idRelatedFile);
			es.mets = mets;			
		 }
		 else
		 { 
			 LinkedFiles lf = getLinkedFiles(es.idRelatedFile,es.filePart);
			 MetsFile mets = getMets(lf.idMets);
			 es.mets = mets;
			 es.linkedFiles = lf;		 
		 }
		 v.push_back(es);		 
	  }
	}
	sqlite3_finalize(pStmt);
	return v;
}

/// <summary>get a vector of all the errortype found for a specific category of the testset </summary>
/// <param name="id_cat">id_cat</param>
/// <param name="id_testset">id testset</param>
/// <returns>int count</returns>
std::vector<ErrorType> dbrequest::getDistinctErrorType(int id_cat,int id_testset)
{	
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::stringstream oid,oidcat;
	std::vector<ErrorType> v;
	oid << id_testset;	
	oidcat << id_cat;
	sqlite3_stmt *pStmt;	
	const char *zErrMsg= 0;    
	std::string selectSql = "select distinct(ID_TYPE) from ERRORTYPE e,MetsError s where s.ID_ERRORTYPE = e.id and id_testset ='" + oid.str() + "'and e.ID_CATEGORY = '" + oidcat.str() + "'";  
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	std::map<int,int> mapYearCount;
	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{				
			const char *result = (const char *)sqlite3_column_text(pStmt, 0);			
			v.push_back(getErrorTypeWithId(atoi(result)));		 
		}
   } 
	sqlite3_finalize(pStmt);
   return v;
}

/// <summary>get a vector of Errorcategory</summary>	
/// <returns>vector of Errorcategory</returns>	
std::vector<ErrorCategory> dbrequest::getErrorCategory()
{
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::vector<ErrorCategory> v;
	ErrorCategory ec;	
	sqlite3_stmt *pStmt;
	const char *zErrMsg= "";    
    std::string selectSql = "select * from ERRORCATEGORY";  
	DEBUG_ME
    int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	std::map<int,int> mapYearCount;
    if(rc == SQLITE_OK)
    {	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			int count = sqlite3_data_count(pStmt);		
			for (int i =0;i<  count ;i++)
			{
				const char *result = (const char *)sqlite3_column_text(pStmt, i);
				if (i==0) ec.id= atoi(result); 							
				else if (i==1) ec.id_category = atoi(result);
				else if (i==2) ec.name = result;				
			}	
			v.push_back(ec);		 
		}
   } 
	sqlite3_finalize(pStmt);
   return v;
}

/// <summary>get a vector of Mets errors filter by category or errortype </summary>
/// <param name="error">string error</param>
/// <param name="id_testset">id testset</param>
/// <returns>int count</returns>
std::vector<MetsError> dbrequest::getErrorFilter(std::string error,int id_testset,int id_cat)
{	
	std::vector<MetsError> v ;
	ConnectionDB conn = g_pool.getConnection(databaseName);
	MetsError es;
	sqlite3_stmt *pStmt;	
	std::stringstream sId_testset,sYear,sId_cat;
	sId_testset << id_testset;	
	sId_cat << id_cat;
	const char *zErrMsg= 0; 
	std::string selectSql = "select s.ID,s.ID_RELATED,s.RELATED_TYPE,s.FILE_PART,s.ERRORLINE,s.ERRORCOLUMN,s.MESSAGE,s.ID_ERRORTYPE,s.id_search from MetsError s,ERRORTYPE e where s.ID_ERRORTYPE = e.ID  and s.ID_TESTSET = '"+ sId_testset.str() + "'";
	if (error !="")
	{
		selectSql = selectSql +	" and e.ERROR = '"+ error + "'";
	}
	else
	{
		selectSql = selectSql +" and e.id_category = '" + sId_cat.str() + "'";
	}
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	if(rc == SQLITE_OK)
	{	  
      while(sqlite3_step(pStmt) == SQLITE_ROW)
      {
		int count = sqlite3_data_count(pStmt);		
		 for (int i =0;i<  count ;i++)
		 {
			const char *result = (const char *)sqlite3_column_text(pStmt, i);
			if (i==0) es.id= atoi(result); 							
			else if (i==1) es.idRelatedFile = atoi(result);
			else if (i==2) es.relatedType = result;	
			else if (i==3) es.filePart = result;
			else if (i==4) es.errorLine = atoi(result);
			else if (i==5) es.errorColumn = atoi(result);
			else if (i==6) es.message = result;
			else if (i==7) es.errorType = getErrorTypeWithId(atoi(result));
			else if (i==8) es.id_search = result;
		 }

		 if (strcmp(es.relatedType.c_str(),"METS") == 0)
		 {
			MetsFile mets = getMets(es.idRelatedFile);
			es.mets = mets;			
		 }
		 else
		 { 
			 LinkedFiles lf = getLinkedFiles(es.idRelatedFile,es.filePart);
			 MetsFile mets = getMets(lf.idMets);
			 es.mets = mets;
			 es.linkedFiles = lf;		 
		 }
		 v.push_back(es);		 
	  }
   }
	sqlite3_finalize(pStmt);
	return v;
}


/// <summary>get DateError found by the metsverfier</summary>
/// <param name="id_testset">id testset</param>
/// <returns>vector of DateError</returns>
std::vector<DateError> dbrequest::getDateError(int id_testset)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);
	
	DateError de;
	std::stringstream oId;
	oId << id_testset;	
	std::vector<DateError> v;
    sqlite3_stmt *pStmt;
	const char *zErrMsg= 0; 
	Article article;	
	std::string selectSql = "SELECT de.id,de.id_testset,de.date_begin,de.date_end, de.issues,de.comment,de.id_errortype FROM DATEERROR de where de.ID_testset ='" + oId.str() + "'";
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	if(rc == SQLITE_OK)
	{	  
      while(sqlite3_step(pStmt) == SQLITE_ROW)
      {
		int count = sqlite3_data_count(pStmt);
		std::pair<int,DateError> p;
		 for (int i =0;i<  count ;i++)
		 {
			const char *result = (const char *)sqlite3_column_text(pStmt, i);
			
			if (i==0)
			{ 
				de.id = atoi(result);
				de.dateComment = getDateCommentid(atoi(result));				
			}							
			else if (i==1) de.id_testset = atoi(result);
			else if (i==2) de.dateBegin = result;
			else if (i==3) de.dateEnd = result;
			else if (i==4) de.issues = result;		
			else if (i==5) de.comment = result;			
			else if (i==6) de.errortype = getErrorTypeWithId(atoi(result));					
		 }		
		 v.push_back(de);
	  }
	}
	sqlite3_finalize(pStmt);
	return v;
}

/// <summary>fill combobox of type of date category</summary>
/// <param name="id_cat">id cat</param>
/// <param name="id_testset">id_testset</param>
/// <returns>vector of DateError</returns>
std::vector<std::string> dbrequest::getDistinctErrorTypeDateError(int id_cat,int id_testset)
{	
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::stringstream oid,oidcat;
	std::vector<std::string> v;
	oid << id_testset;	
	oidcat << id_cat;	
    sqlite3_stmt *pStmt;	
	const char *zErrMsg= 0;    
    std::string selectSql = "select distinct(Error) from ERRORTYPE e,DATEERROR s where s.ID_ERRORTYPE = e.id_type ";  
	DEBUG_ME
    int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	std::map<int,int> mapYearCount;
    if(rc == SQLITE_OK)
    {	  
      while(sqlite3_step(pStmt) == SQLITE_ROW)
      {			
		const char *result = (const char *)sqlite3_column_text(pStmt, 0);			
		v.push_back(result);		 
	  }
   } 
	sqlite3_finalize(pStmt);
   return v;
}

/// <summary>get comment of a date of the selected date</summary>
/// <param name="idError">idError</param>
/// <returns>vector of DateComment of the current DateError</returns>
std::vector<DateComment> dbrequest::getDateCommentid(int idError)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);
	DateComment dc;
	std::stringstream oId;
	oId << idError;	
	std::vector<DateComment> v;
    sqlite3_stmt *pStmt;	
	const char *zErrMsg= 0; 
	Article article;	
	std::string selectSql = "SELECT dc.id, dc.id_dateerror, dc.date, dc.comment FROM DATECOMMENT dc where id_dateerror ='" + oId.str() + "'" ;
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	if(rc == SQLITE_OK)
	{	  
      while(sqlite3_step(pStmt) == SQLITE_ROW)
      {
		int count = sqlite3_data_count(pStmt);
		std::pair<int,DateError> p;
		 for (int i =0;i<  count ;i++)
		 {
			const char *result = (const char *)sqlite3_column_text(pStmt, i);			
			if (i==0)
			{ 
				dc.id = atoi(result);				
			}							
			else if (i==1) dc.id_DateError = atoi(result);			
			else if (i==2) dc.date = dc.date.fromString(result,"yyyy-MM-dd");		
			else if (i==3) dc.comment = result;			
		 }		
		v.push_back(dc);	 
	  }
	}
	sqlite3_finalize(pStmt);
	return v;
}



std::map<int,StructureError> dbrequest::getStructureError(int id_Mets)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);	
	sqlite3_stmt *pStmt;
	std::stringstream sId_mets;	
	sId_mets << id_Mets;
	int rc;	
	const char *zErrMsg= ""; 
	std::string selectSql = "SELECT * FROM STRUCTUREERROR where ID_METS = '"+ sId_mets.str()  +"'"; 
	std::map<int,StructureError> v;
	DEBUG_ME
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	StructureError se;  
	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			
			int count = sqlite3_data_count(pStmt);		
			for (int i =0;i<  count ;i++)
			{
				const char *result = (const char *)sqlite3_column_text(pStmt, i);			
				if (i==0) se.id = atoi(result);							
				else if (i==1) se.id_mets = atoi(result);
				else if (i==2) se.pathImage = result; 
				else if (i==3) se.message = result;
				else if (i==4) se.errorType = getErrorTypeWithId(atoi(result));					
			}
			v[se.id]= se; 			 
		}		
   }
	sqlite3_finalize(pStmt);
	return v;
}



std::vector<Sampling_Structure> dbrequest::getListSamplingStructure(int id_testset)
{	
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::stringstream oIdTestset,oYear;
	oIdTestset << id_testset;	
	//oYear << year;
    sqlite3_stmt *pStmt;
	int rc;	
	const char *zErrMsg= ""; 
	Sampling_Structure ss;
	std::vector<Sampling_Structure>  v;
	std::string selectSql = "select * from SAMPLING_STRUCTURE ss, METS m where ss.ID_METS = m.ID_METS and m.ID_TESTSET  ='" + oIdTestset.str() + "'";
	DEBUG_ME
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);

	if(rc == SQLITE_OK)
	{	  
      while(sqlite3_step(pStmt) == SQLITE_ROW)
      {
		int count = sqlite3_data_count(pStmt);		
		 for (int i =0;i<  count ;i++)
		 {
			const char *result = (const char *)sqlite3_column_text(pStmt, i);
			
			if (i==0)
			{ 
				ss.id = atoi(result);			
			}
							
			else if (i==1) ss.id_Mets = atoi(result);
			else if (i==2) ss.checked = atoi(result);				
		 }	
		 
		 ss.Mets = getMets(ss.id_Mets);	
		 v.push_back(ss);
		 
	  }
   }
	sqlite3_finalize(pStmt);
   return v;   
}

void dbrequest::updateSamplingStructure(int id,int checked)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);
	char *zErrMsg =0;
	std::stringstream o,oChecked;
	o << id;	
	oChecked << checked;
	std::string sql =	"UPDATE SAMPLING_STRUCTURE SET CHECKED = '" + oChecked.str() + "' where ID = '"+ o.str() +"'";					
		
	int rc = sqlite3_exec(conn.db, sql.c_str(), NULL, 0, &zErrMsg); //null because no calll back needed
	
	if( rc )
	{
		fprintf(stderr, "Can't update data SAMPLING_STRUCTURE: %s\n",  zErrMsg);
	}
}

std::vector<ErrorType> dbrequest::getErrorTypeCatStructure()
{
	ConnectionDB conn = g_pool.getConnection(databaseName);	
	sqlite3_stmt *pStmt;
	int rc;	
	const char *zErrMsg= 0; 
	
	std::string selectSql = "SELECT * FROM ERRORTYPE where ID_CATEGORY = 6"; 
	std::vector<ErrorType> v;
	DEBUG_ME
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	ErrorType et;  
	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			
			int count = sqlite3_data_count(pStmt);		
			for (int i =0;i<  count ;i++)
			{
				const char *result = (const char *)sqlite3_column_text(pStmt, i);			
				if (i==0) et.id = atoi(result);	
				else if (i==1) et.id_type = atoi(result);						
				else if (i==2) et.error = result;
				else if (i==3) et.details = result;
				else if (i==4) 
				{
					et.severity = getErrorSeverityWithId(atoi(result));
					et.id_severity = atoi(result);		
				}	
				else if (i==5) et.category = getErrorCategoryWithId(atoi(result));
						
			}
			v.push_back(et);				 
		}		
   }
	sqlite3_finalize(pStmt);
	return v;
}

bool dbrequest::saveStructError(int id_mets,std::string message,int idErrorType,std::string path)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::stringstream sId_mets,sIdError;	
	sId_mets << id_mets;
	sIdError << idErrorType;
	 char *zErrMsg=0;
	std::string sql = "INSERT INTO STRUCTUREERROR ('ID_METS','IMAGEPATH', 'MESSAGE','ID_ERRORTYPE') \
					  VALUES  ('" + sId_mets.str() + "','" + path + "','" + message + "','" + sIdError.str() +"')"; 							

	int rc = sqlite3_exec(conn.db, sql.c_str(), NULL, 0, &zErrMsg); 	
	if( rc )
	{
		fprintf(stderr, "Can't insert data TestSet: %s\n",zErrMsg);
		return false;
	}
	return true; 
}


std::vector<Title> dbrequest::getvTitle(int id_testset)
{	
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::stringstream oIdTestset,oYear;
	oIdTestset << id_testset;		
    sqlite3_stmt *pStmt;
	int rc;	
	const char *zErrMsg= 0; 
	Title title;
	std::vector<Title>  vTitle;
	std::string selectSql ="select t.id,t.id_article, m.id_mets,a.countcaracter,t.errorcount,a.title from TITLECHECK t, \
	ARTICLE a,METS m where  t.id_article = a.id and m.id_mets = a.id_mets and m.id_testset = '"+ oIdTestset.str() +"' order by t.id ";
	DEBUG_ME
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);

	if(rc == SQLITE_OK)
	{	  
      while(sqlite3_step(pStmt) == SQLITE_ROW)
      {
		int count = sqlite3_data_count(pStmt);
		std::pair<int,DateError> p;
		for (int i =0;i<  count ;i++)
		{
			const char *result = (const char *)sqlite3_column_text(pStmt, i);
			
			if (i==0)title.id = atoi(result);							
			else if (i==1)
			{ 
				title.id_article = atoi(result);
				title.article = getArticle(atoi(result));
			}
			else if (i==2)
			{ 
				title.id_mets = atoi(result);
				title.mets = getMets(atoi(result));
			}
			else if (i==3) title.countString = atoi(result);
			else if (i==4)title.countError = atoi(result);					
			else if (i==5) title.title = result;			
		}	
		vTitle.push_back(title);
		 
	  }
   }
	sqlite3_finalize(pStmt);
   return vTitle;
}


Article dbrequest::getArticle(int id)
{
Article a;

	ConnectionDB conn = g_pool.getConnection(databaseName);

	std::stringstream oId;
	oId << id;	
	//oYear << year;
    sqlite3_stmt *pStmt;
	int rc;	
	const char *zErrMsg= 0; 
	Article article;	
	std::string selectSql = "SELECT * FROM Article where ID ='" + oId.str() + "'";
	DEBUG_ME
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);

	if(rc == SQLITE_OK)
	{	  
      while(sqlite3_step(pStmt) == SQLITE_ROW)
      {
		int count = sqlite3_data_count(pStmt);
		std::pair<int,DateError> p;
		 for (int i =0;i<  count ;i++)
		 {
			const char *result = (const char *)sqlite3_column_text(pStmt, i);
			
			if (i==0)
			{ 
				article.id = atoi(result);				
			}
							
			else if (i==1) article.id_mets = atoi(result);
			else if (i==2) article.id_article = result;
			else if (i==3) article.div = result;
			else if (i==4)	article.check = atoi(result);		
			else if (i==5) article.title = result;
			else if (i==6) article.countcaracter = atoi(result);		
	//		else if (i==7) article.number = atoi(result);		
		 }		
		 
	  }
   }
	sqlite3_finalize(pStmt);
	return article;
}


std::pair<int,int> dbrequest::getSumCharacter(int id)
{
	Article a;
	ConnectionDB conn = g_pool.getConnection(databaseName);
	std::stringstream oId;
	std::pair<int,int> pair;
	pair.first =0;
	pair.second =0;
	oId << id;	
	
    sqlite3_stmt *pStmt;
	int rc;	
	const char *zErrMsg= 0; 		
	std::string selectSql = "select sum (countcaracter),sum(errorcount) from article a, titlecheck t, mets m where t.id_article = a.id and  \
	a.id_mets = m.id_mets and m.id_testset ='" + oId.str() + "'";
	DEBUG_ME
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);

	if(rc == SQLITE_OK)
	{	  
      while(sqlite3_step(pStmt) == SQLITE_ROW)
      {
		int count = sqlite3_data_count(pStmt);
		std::pair<int,DateError> p;
		 for (int i =0;i<  count ;i++)
		 {
			const char *result = (const char *)sqlite3_column_text(pStmt, i);			
			if (i==0){ pair.first = atoi(result);}							
			else if (i==1) pair.second = atoi(result);	
		 }		
		 
	  }
   }
	sqlite3_finalize(pStmt);
	return pair;
}


void dbrequest::updateTitleError(int id,int caract)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);
	char *zErrMsg =0;
	std::stringstream o,oCaract;
	o << id;
	oCaract << caract;	
	std::string sql =	"UPDATE TITLECHECK SET ERRORCOUNT  ='" + oCaract.str() + "' where ID = '"+ o.str() +"'";					
		
	int rc = sqlite3_exec(conn.db, sql.c_str(), NULL, 0, &zErrMsg); //null because no calll back needed
	
	if( rc )
	{
		fprintf(stderr, "Can't update data ERRORCOUNT: %s\n",  zErrMsg);
	}
}

std::vector<Excel> dbrequest::getInventaire(int id)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);	
	sqlite3_stmt *pStmt;
	std::stringstream sIdNews;
	sIdNews << id;	
	Excel excel;		
	const char *zErrMsg= 0; 
		std::string selectSql = "SELECT e.id,e.id_sheet,e.day,e.month,e.year,e.issue_number,e.pages,e.supplement,e.suppl_pages,e.type,e.jg,e.annexes,e.missing from  Excel e , SHEET s where S.ID = e.ID_SHEET and s.ID_NEWSPAPER ='" + sIdNews.str()+ "'"; 	

	std::vector<Excel> v;
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);	
	
	if(rc == SQLITE_OK)
	{	  
      while(sqlite3_step(pStmt) == SQLITE_ROW)
      {
		int count = sqlite3_data_count(pStmt);		
		 for (int i =0;i<  count ;i++)
		 {
			const char *result = (const char *)sqlite3_column_text(pStmt, i);
			
			if (i==0) excel.id = atoi(result);								
			else if (i==1) 	excel.id_sheet = atoi(result);	
			else if (i==2) excel.day = atoi(result);
			else if (i==3) excel.month = atoi(result);
			else if (i==4) excel.year = atoi(result);		
			else if (i==5) excel.issueNumber = getIssueNumberExcel(result);	
			else if (i==6) excel.pages = atoi(result);		
			else if (i==7) excel.supplement = result;
			else if (i==8) excel.supPages = atoi(result);	
			else if (i==9) excel.type = result;		
			else if (i==10) excel.jg = atoi(result);
			else if (i==11) excel.annexes = atoi(result);
			else if (i==12) excel.missing = atoi(result);					
		 }	
		 v.push_back(excel);		
	  }
   }
	sqlite3_finalize(pStmt);
	return v;
}



std::map<QDate,std::vector<Excel> > dbrequest::getMapInventaire(int id)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);	
	sqlite3_stmt *pStmt;
	std::stringstream sIdNews;
	Excel excel;
	std::map<QDate,std::vector<Excel> > mapInv;
	std::vector<Excel> vExcel;	
	sIdNews <<id;
	
	const char *zErrMsg= 0; 
	std::string selectSql = "SELECT e.id,e.id_sheet,e.day,e.month,e.year,e.issue_number,e.pages,e.supplement,e.suppl_pages,e.type,e.jg,e.annexes,e.missing from  Excel e , SHEET s where S.ID = e.ID_SHEET and s.ID_NEWSPAPER ='" + sIdNews.str()+ "'"; 	
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);	
	
	if(rc == SQLITE_OK)
	{	  
      while(sqlite3_step(pStmt) == SQLITE_ROW)
      {
		int count = sqlite3_data_count(pStmt);		
		 vExcel.clear();	
		 for (int i =0;i<  count ;i++)
		 {
			const char *result = (const char *)sqlite3_column_text(pStmt, i);
			
			if (i==0) excel.id = atoi(result);								
			else if (i==1) 	excel.id_sheet = atoi(result);	
			else if (i==2) excel.day = atoi(result);
			else if (i==3) excel.month = atoi(result);
			else if (i==4) excel.year = atoi(result);		 
			else if (i==5) excel.issueNumber = getIssueNumberExcel(result);	
			else if (i==6) excel.pages = atoi(result);		
			else if (i==7) excel.supplement = result;
			else if (i==8) excel.supPages = atoi(result);	
			else if (i==9) excel.type = result;		
			else if (i==10) excel.jg = atoi(result);
			else if (i==11) excel.annexes = atoi(result);
			else if (i==12) excel.missing = atoi(result);					
		 }		
		excel.date.setDate(excel.year,excel.month,excel.day);
		
		
		if (mapInv.find(excel.date) == mapInv.end())
		{
			 vExcel.push_back(excel);
			 mapInv[excel.date] = vExcel;			
		}
		else
		{
			mapInv[excel.date].push_back(excel);
		}		
			
	  }
   }
	sqlite3_finalize(pStmt);
	return mapInv;
}

std::vector<Inventaire> dbrequest::getNameInventaire()
{
	ConnectionDB conn = g_pool.getConnection(databaseName);	
	sqlite3_stmt *pStmt;
	Inventaire inv;	
	
	const char *zErrMsg= 0; 
	std::string selectSql = "SELECT ID,CODE,NAME from  NEWSPAPER"; 
	std::vector<Inventaire> v;
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);	
	
	if(rc == SQLITE_OK)
	{	  
      while(sqlite3_step(pStmt) == SQLITE_ROW)
      {
		int count = sqlite3_data_count(pStmt);		
		 for (int i =0;i<  count ;i++)
		 {
			const char *result = (const char *)sqlite3_column_text(pStmt, i);
			
			if (i==0) inv.id = atoi(result);								
			else if (i==1) 	inv.code = result;	
			else if (i==2) inv.name = result;				
		 }	
		 v.push_back(inv);		
	  }
   }
	sqlite3_finalize(pStmt);
	return v;

}

std::vector<int> dbrequest::getMetsIdInPeriod(int id_testset, int year_from, int month_from, int year_to, int month_to)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);	
	sqlite3_stmt *pStmt;
	
	const char *zErrMsg= 0; 
	
	std::stringstream clause;
	clause << "ID_TESTSET='" << id_testset << "' AND DATE>='" << year_from << "-" << month_from << "01' AND DATE<'" << year_to << "-" << month_to << "01';";
	std::string selectSql = "SELECT ID_METS FROM METS WHERE " + clause.str();
	std::vector<int> v;
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);	

	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			int result = sqlite3_column_int(pStmt, 0);
			v.push_back(result);
		}
	}
	sqlite3_finalize(pStmt);
	return v;
}

std::vector<QDate> dbrequest::getMetsDateInPeriod(int id_testset, int year_from, int month_from, int year_to, int month_to)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);	
	sqlite3_stmt *pStmt;
	
	const char *zErrMsg= 0; 
	
	std::stringstream clause;
	clause << "ID_TESTSET='" << id_testset << "' AND DATE>='" << year_from << "-" << std::setw(2) << std::setfill('0') << month_from << "-01' AND DATE<'" << year_to << "-" << std::setw(2) << std::setfill('0') << month_to << "-01';";
	std::string selectSql = "SELECT DATE FROM METS WHERE " + clause.str();
	std::vector<QDate> v;
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	QDate temp;

	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			const char * result = (const char *) sqlite3_column_text(pStmt, 0);
			v.push_back(temp.fromString(result, "yyyy-MM-dd"));
		}
	}
	sqlite3_finalize(pStmt);
	return v;
}

std::vector<QDate> dbrequest::getMetsDateInMonth(int id_testset, int year, int month)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);	
	sqlite3_stmt *pStmt;
	
	const char *zErrMsg= 0;
	int year_to;
	int month_to;
	if (month == 12) {
		month_to = 1;
		year_to = year + 1;
	} else {
		month_to = month + 1;
		year_to = year;
	}
	
	std::stringstream clause;
	clause << "ID_TESTSET='" << id_testset << "' AND DATE>='" << year << "-" << std::setw(2) << std::setfill('0') << month << "-01' AND DATE<'" << year_to << "-" << std::setw(2) << std::setfill('0') << month_to << "-01';";
	std::string selectSql = "SELECT DATE FROM METS WHERE " + clause.str();
	std::vector<QDate> v;
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	QDate temp;

	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			const char * result = (const char *) sqlite3_column_text(pStmt, 0);
			v.push_back(temp.fromString(result, "yyyy-MM-dd"));
		}
	}
	sqlite3_finalize(pStmt);
	return v;
}
std::vector<QDate> dbrequest::getMetsDates(int id_testset)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);	
	sqlite3_stmt *pStmt;
	
	const char *zErrMsg= 0; 
	
	std::stringstream clause;
	clause << "ID_TESTSET='" << id_testset << "'";
	std::string selectSql = "SELECT DATE FROM METS WHERE " + clause.str();
	std::vector<QDate> v;
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);	
	QDate temp;
	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			const char * result = (const char *) sqlite3_column_text(pStmt, 0);
			v.push_back(temp.fromString(result, "yyyy-MM-dd"));
		}
	}
	sqlite3_finalize(pStmt);
	return v;
}

// Get the number of (METS, supplements) per year
std::map<int ,std::pair<int, int> > dbrequest::GetYearSummary(int id_testset)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);	
	sqlite3_stmt *pStmt;
	
	const char *zErrMsg= 0; 
	
	// First get the number of METS files per year
	std::stringstream clause;
	clause << "ID_TESTSET='" << id_testset << "' GROUP BY YEAR";
	std::string selectSql = "SELECT YEAR, COUNT(ID_METS) FROM METS WHERE " + clause.str();
	std::map<int ,std::pair<int, int> > v;
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);	
	
	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			int resYear = sqlite3_column_int(pStmt, 0);
			int resCountMets = sqlite3_column_int(pStmt, 1);
			v[resYear].first = resCountMets;
		}
	}
	sqlite3_finalize(pStmt);
	
	// Now get the number of supplements per year
	clause.clear();
	clause.str(std::string());
	clause << "ID_TESTSET=" << id_testset << " AND S.ID_METS=M.ID_METS GROUP BY YEAR";
	selectSql = "SELECT M.YEAR, COUNT(S.ID) FROM METS M, SUPPLEMENTS S WHERE " + clause.str();
	DEBUG_ME
	rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);	
	
	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			int resYear = sqlite3_column_int(pStmt, 0);
			int resCountSuppl = sqlite3_column_int(pStmt, 1);
			v[resYear].second = resCountSuppl;
		}
	}
	sqlite3_finalize(pStmt);

	return v;
}

std::vector<MetsFile> *dbrequest::getMetsByDate(int id_testset, QDate date)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);	
	sqlite3_stmt *pStmt;

	const char *zErrMsg= 0; 
	
	// First get the number of METS files per year
	std::stringstream clause;
	clause << "ID_TESTSET='" << id_testset << "' AND DATE='" << qPrintable(date.toString("yyyy-MM-dd")) << "'";
	std::string selectSql = "SELECT ID_METS FROM METS WHERE " + clause.str();
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);	
	
	if(rc == SQLITE_OK)
	{	  
		std::vector<MetsFile> *result = new std::vector<MetsFile>;
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			int id_mets = sqlite3_column_int(pStmt, 0);
			result->push_back(getMets(id_mets));
		}
		sqlite3_finalize(pStmt);
		return result;
	} else {
		sqlite3_finalize(pStmt);
		return 0;
	}
}

std::string dbrequest::getFirstMetsFilename(int id_testset)
{
	ConnectionDB conn = g_pool.getConnection(databaseName);	
	sqlite3_stmt *pStmt;

	const char *zErrMsg= 0; 
	
	// First get the number of METS files per year
	std::stringstream clause;
	clause << "ID_TESTSET='" << id_testset << "' LIMIT 1";
	std::string selectSql = "SELECT PATH, FILENAME FROM METS WHERE " + clause.str();
	DEBUG_ME
	int rc = sqlite3_prepare_v2(conn.db,selectSql.c_str(),-1, &pStmt,&zErrMsg);
	std::string res;
	
	if(rc == SQLITE_OK)
	{	  
		while(sqlite3_step(pStmt) == SQLITE_ROW)
		{
			const char *path = (const char *) sqlite3_column_text(pStmt, 0);
			const char *filename = (const char *) sqlite3_column_text(pStmt, 1);
			res = path + std::string("/") + filename;
		}
		
	}
	sqlite3_finalize(pStmt);
	return res;
}