#ifndef DBREQUEST_H_
#define DBREQUEST_H_

#include "sqlite3.h"
#include <vector>
#include "structgui.h"
#include <map>
#include <QDate>
#include <QVariant>

struct ConnectionDB
{
	sqlite3 *db;
#ifdef LOG_TIMING
	FILE *fpLog;
#endif
	ConnectionDB();
	bool openConnection(const std::string &dbname);
	~ConnectionDB();
private:
	void close();
};

class ConnectionPool
{
public:
	ConnectionDB* getConnection(const std::string &dbname);
	~ConnectionPool();
private:
	std::map<std::string, ConnectionDB*> Databases;
};

extern ConnectionPool g_pool;

class dbrequest
{
	private:
		//sqlite3 *db;
		std::string databaseName;
		//FILE *fpLog;
		//void closeDB();
		Parameters _getParameterVerifiers(int id_testset);
	public:	

		//set database
		void setDataBaseName(std::string dbName);
		// bool openDB();
		//return a vector of all testsets from batch
		std::vector<std::string> getvTestSet();
		std::map<std::string,std::string> key2Label(std::map<std::string,std::string>);
		std::string getLabel(std::string);
		// get a vector of  all tests from selected Batch
		std::vector<std::pair<int,std::string> > getvDateTestset(std::string batch);
		//return the details from the selected Batch 
		void getBatch(BatchDetail& bdetail,int id_testset);
		// return the parameters of verified tests
		Parameters getParameterVerifiers(int id_testset);
	/// <summary>getTestset id's of selected batch</summary>
	/// <param name="id">batchName</param>
	/// <returns>vector of testset id's</returns>
//--> pas besoin pour le moment
		std::vector<int> getIdTestset(std::string batchName);		
	/// <summary>get the summary of the errors of the current testset (without dates) </summary>
	/// <param name="id">id_testset</param>
	/// <returns>vector of ErrorSummary</returns>
		std::vector<ErrorSummary> getvErrorSummary(int id_testset);	
	/// <summary>get the summary of the date errors of the current testset</summary>
	/// <param name="id">id_testset</param>
	/// <returns>vector of ErrorSummary</returns>
		std::vector<ErrorSummary> getvErrorDate(int id_testset);		
	/// <summary>get Errortype of the current id </summary>
	/// <param name="id">id of type of error</param>
	/// <returns>ErrorType</returns>
		ErrorType getErrorTypeWithId(int id);
	/// <summary>get ErrorSeverity of the current id of ErrorType </summary>
	/// <param name="id">id of Errortype</param>
	/// <returns>ErrorSeverity</returns>
		ErrorSeverity getErrorSeverityWithId(int id);
	/// <summary>get ErrorCategory of the current id of ErrorType </summary>
	/// <param name="id">id of Errortype</param>
	/// <returns>ErrorCategory</returns>
		ErrorCategory getErrorCategoryWithId(int id);
	/// <summary>get ErrorCategory of the current id of ErrorType </summary>
	/// <returns>vector of ErrorType</returns>
		std::vector<ErrorType> getErrorType();
	/// <summary>count number of date error </summary>
	/// <param name="id">id  Errortype</param>
	/// <param name="id">id testset</param>
	/// <returns>int count</returns>
		int getErrorTypeCountWithTestsetDates(int idError,int id_testset);
	/// <summary>count number of error for distinct errortype </summary>
	/// <param name="id">id of Errortype</param>
	/// <param name="id">id testset</param>
	/// <returns>int count</returns>
		int getErrorTypeCountWithTestset(int idError,int id_testset);
	/// <summary>get all mets</summary>
	/// <param name="id">id _testset</param>
	/// <returns>map int,MetsFile </returns>		
		std::map<QDate,std::vector<int> > getmMetsDate(int id_testset);
	/// <summary>get linked files of an mets for the selected group</summary>
	/// <param name="idMets">idMets</param>
	/// <param name="fileGroup">string fileGroup</param>
	/// <returns>map int,LinkedFiles </returns>
		std::map<int,LinkedFiles> getMapLinkedFiles(int idMets,std::string fileGroup);
	/// <summary>get the total of mets per year</summary>
	/// <param name="id_testset">id_testset</param>
	/// <returns>map year - pair total mets,total Supplement</returns>
		std::map<int,std::pair<int,int>> getSumMetsYear(int id_testset);
	/// <summary>get the total of supplements</summary>
	/// <param name="id_testset">id_testset</param>
	/// <param name="year">current year</param>
	/// <returns>sum of supllement for the year</returns>
		int getSumSupplYear(int id_testset,int year);
	/// <summary>get comments of specific date</summary>
	/// <param name="id_testset">id_testset</param>
	/// <returns>map of date,DateComment </returns>
		std::map<QDate,DateComment> getDateComment(int id_testset);
	/// <summary>get vector of date error found by mets verifier</summary>
	/// <param name="id_testset">id_testset</param>
	/// <returns>vector with pair id,DateError </returns>
		std::vector<std::pair<int,DateError>>getvDateError(int id_testset);
	///<summary>upadte comment of calendar</summary>
		void updateDateComment(int id,std::string comment);
	///<summary>insert comment of calendar</summary>
		bool insertComment(int id_mets,std::string date, std::string comment);
	/// <summary>count of erros of each errotype</summary>
	/// <param name="idTestset">id testset</param>
	/// <param name="errortype">id errortype</param>
	/// <returns>int</returns>
		int getcountMetsErrorForEachErrorType(int idTestset,int errortype);	
	/// <summary>count of schema Errors except dates</summary>
	/// <param name="id">id testset</param>
	/// <returns>int</returns>
		int getcountMetsError(int idTestset);
	/// <summary>count number of titles to check </summary>
	/// <param name="id">id testset</param>
	/// <returns>int count</returns>
		int getcountTitleCheck(int id_testset);
	/// <summary>get a vector of Mets errors </summary>
	/// <param name="id_cat">id category</param>
	/// <param name="id_testset">id testset</param>
	/// <returns>int count</returns>
		std::vector<MetsError>getvErrorPerCategory(int id_cat, int idTestset);	
	/// <summary>get a vector of Mets errors filter by category </summary>
	/// <param name="error">string error</param>
	/// <param name="id_testset">id testset</param>
	/// <returns>int count</returns>
		std::vector<ErrorType> getDistinctErrorType(int id_cat,int id_testset);
	/// <summary>get details of a mets</summary>	
	/// <param name="id_metst">id mets</param>
	/// <returns>MetsFile</returns>	
		MetsFile getMets(int id_mets);
	/// <summary>get details of LinkedFiles</summary>	
	/// <param name="id_mets">id of mets </param>
	/// <param file_part="">filepart(alto,img,pdf)</param>
	/// <returns>LinkedFiles</returns>	
		LinkedFiles getLinkedFiles(int id,std::string file_part);
		
		std::vector<ErrorCategory> getErrorCategory();
	/// <summary>get a vector of Mets errors filter by category or errortype </summary>
	/// <param name="error">string error</param>
	/// <param name="id_testset">id testset</param>
	/// <returns>int count</returns>
		std::vector<MetsError> getErrorFilter(std::string error,int id_testset,int id_cat);
	/// <summary>get DateError found by the metsverfier</summary>
	/// <param name="id_testset">id testset</param>
	/// <returns>vector of DateError</returns>
		std::vector<DateError> getDateError(int id_testset);
	/// <summary>fill combobox of type of date category</summary>
	/// <param name="id_cat">id cat</param>
	/// <param name="id_testset">id_testset</param>
	/// <returns>vector of DateError</returns>
		std::vector<std::string> getDistinctErrorTypeDateError(int id_cat,int id_testset);
	/// <summary>get comment of a date of the selected date</summary>
	/// <param name="idError">idError</param>
	/// <returns>vector of DateComment of the current DateError</returns>
		std::vector<DateComment> getDateCommentid(int idError);		
		
		std::map<int,StructureError> getStructureError(int id_Mets);	
		std::vector<Sampling_Structure> getListSamplingStructure(int id_testset);	
		void updateSamplingStructure(int id,int checked);
		std::vector<ErrorType> getErrorTypeCatStructure();
		bool saveStructError(int id_mets,std::string message,int idErrorType,std::string path,std::string);
		std::vector<Title> getvTitle(int id_testset);
		Article getArticle(int id);
		std::pair<int,int> getSumCharacter(int id);
		void updateTitleError(int id,int caract);		
		std::vector<Excel> getInventaire(int id);
		std::map<QDate,std::vector<Excel> >getMapInventaire(int id);
		
		/// <summary>get all inventory from the selected database</summary>		
		/// <returns>vector of inventory</returns>
		std::vector<Inventaire> getNameInventaire();
		

		std::vector<std::vector<QVariant> > getAllMets(int id_testset);
		std::vector<int> getMetsIdInPeriod(int id_testset, int year_from, int month_from, int year_to, int month_to);
		std::vector<QDate> getMetsDateInPeriod(int id_testset, int year_from, int month_from, int year_to, int month_to);
		std::vector<QDate> getMetsDateInMonth(int id_testset, int year, int month);
		std::vector<QDate> getMetsDates(int id_testset);
		std::map<int ,std::pair<int, int> > GetYearSummary(int id_testset);
		std::vector<MetsFile> *getMetsByDate(int id_testset, QDate date);
		std::string getFirstMetsFilename(int id_testset);
};
#endif // DBREQUEST_H_