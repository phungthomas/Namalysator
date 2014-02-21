#include "insertinventaire.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../common_files/utilities.h"

sqlinventaire::sqlinventaire(const std::string &c,const std::string &n,const std::string &dataBase,std::map<std::string,std::vector<info_t> > *mapInv)
{
	code = c;
	newspaper = n;
	databaseName= dataBase;
	mapInventaire = mapInv;
}

bool sqlinventaire::openDB()
{	
	int rc = sqlite3_open(databaseName.c_str(), &db);
	if( rc )
	{
		fprintf(stderr, "Can not open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return false;
	}	
	return true;
}


int sqlinventaire::getId(const std::string &table)
{		
	const char *zErrMsg =0;
	int id =0;

	sqlite3_stmt *pStmt;   
   
   std::string selectSql = "SELECT max(ID) FROM '"+ table +"'";
   int  rc = sqlite3_prepare_v2(db,selectSql.c_str(),-1, &pStmt,&zErrMsg);

   if(rc == SQLITE_OK)
   {		
		sqlite3_step(pStmt);
		const char *result = (const char *)sqlite3_column_text(pStmt, 0);		
		id = atoi(result);	 
	}  	
	return id;
}

bool sqlinventaire::createTable(const std::string &createTableFile)
{
	std::vector<std::string> vect;
	std::ifstream myfile;
	std::string::size_type found;
	char *zErrMsg = 0;
	openDB();

	std::string sql="";
	std::string value = ");";	
	std::string line;
	myfile.open (createTableFile.c_str());
	const char *sqlCreate;

	if(myfile.fail())
	{			
		myfile.close(); 
		return false;
	}
	else
	{
		while (!myfile.eof())
		{	
			getline (myfile,line);		
			found = line.find(value);
			sql = sql + line; 
			if (found != std::string::npos)
			{
				vect.push_back(sql);				
				sql ="";
			}	
		}
		myfile.close(); 
	
		for (size_t i=0;i < vect.size();i++)
		{
			sqlCreate = vect[i].c_str();
			int rc = sqlite3_exec(db, sqlCreate, NULL, 0, &zErrMsg);
		
			if (rc!=SQLITE_OK )
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);		
				return false;
			}		
		}
		std::cout << "New database created" << std::endl;
	}
	sqlite3_close(db);	
	return true;
}

void sqlinventaire::insertInventaire()
{
	insertNewspaper();
	insertSheet();

}


void sqlinventaire::insertNewspaper()
{	
	char *zErrMsg =0;	
	std::string sql = "INSERT INTO NEWSPAPER ('CODE','NAME') \
					  VALUES   ('" +  code  + "',  \
								'" + newspaper  + "')"; 		

		int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg); //null because no calll back needed
	
		if( rc )
		{	
			#ifdef _DEBUG
				fprintf(stderr, "Can not insert data in database NEWSPAPER: %s\n", &zErrMsg);
			#endif // DEBUG
		  sqlite3_close(db);  
		}		
}

void sqlinventaire::insertSheet()
{	
	char *zErrMsg =0;	
	int id = getId("NEWSPAPER");
	std::stringstream oid;
	oid << id;
	std::string str ("'");
	
	for (std::map<std::string,std::vector<info_t> >::iterator it = mapInventaire->begin(); it != mapInventaire->end(); ++it)
	{			
		std::cout << "insert sheet : " << it->first << std::endl;	
		if (it->second.size() >0)
		{
			std::string header(it->second[0].header);
	
			if (header.find( str )!= string::npos )
			{
				header = replaceApostrophe(header);		
			}
					std::string sql = "INSERT INTO SHEET ('ID_NEWSPAPER','Label','YEAR') \
							  VALUES   ('" +  oid.str()  + "',  \
										'" +  header  + "',  \
										'" +  it->first + "')"; 		
					int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg); //null because no calll back needed
					if( rc )
					{	
						#ifdef _DEBUG
							fprintf(stderr, "Can not insert data in database SHEET: %s\n", &zErrMsg);
						#endif // DEBUG
					  sqlite3_close(db);  
					}		
				insertExcel(it->second);	
			}
		}
	}


std::string replaceApostrophe(std::string message)
{
	for ( size_t i = 0; i < message.length(); i++)
	{
		if (message[i] =='\'')
		{
			message.replace(i,1,"''");
			i+=2; 
		}
	}  
	return message;
}

void sqlinventaire::insertExcel(std::vector<info_t> v)
{	
	char *zErrMsg =0;	
		int id = getId("SHEET");
		std::stringstream oid;
		oid << id;				
			
		for( size_t i=0;i < v.size();i++)
		{		
			std::string supplement(v[i].cells[5] );
			
			supplement = replaceApostrophe(supplement);		
			
		
			std::string sql = "INSERT INTO EXCEL ('ID_SHEET','DAY','MONTH','YEAR','ISSUE_NUMBER','PAGES','SUPPLEMENT',\
			 'SUPPL_PAGES','TYPE','JG','ANNEXES','MISSING') \
					  VALUES   ('" + oid.str() + "',  \
								'" + v[i].cells[0] + "',  \
								'" + v[i].cells[1] + "',  \
								'" + v[i].cells[2] + "',  \
								'" + v[i].cells[3] + "',  \
								'" + v[i].cells[4] + "',  \
								'" +  supplement + "',  \
								'" + v[i].cells[6]+ "',  \
								'" + v[i].cells[7] + "',  \
								'" + v[i].cells[8] + "',  \
								'" + v[i].cells[v[i].cells.size()-2] + "',  \
								'" + v[i].cells[v[i].cells.size()-1]  + "')"; 		
	
			int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg); //null because no calll back needed
		
			if( rc )
			{	
				#ifdef _DEBUG
					fprintf(stderr, "Can not insert data in database excel: %s\n", &zErrMsg);
				#endif // DEBUG
			  sqlite3_close(db);  
			}
			
			for (size_t j =9; j< v[i].cells.size()-2;j++)
			{
				insertVolume(v[i].cells[j]);				
			}						
		}	
}


void sqlinventaire::insertVolume(std::string volume)
{	
	char *zErrMsg =0;	
	int id = getId("Excel");
	std::stringstream oid;
	oid << id;	
	
	
	std::string str ("'");
		
		
	if (volume.find( str )!= string::npos )
	{
		volume = replaceApostrophe(volume);		
	}
		
		std::string sql = "INSERT INTO VOLUME ('ID_EXCEL','DETAIL') \
				  VALUES   ('" +  oid.str()  + "',  \
							'" +  volume  + "')";  
							
		
		int rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg); //null because no calll back needed
		if( rc )
		{	
			#ifdef _DEBUG
				fprintf(stderr, "Can not insert data in database VOLUME: %s\n", &zErrMsg);
			#endif // DEBUG
		  sqlite3_close(db);  
		}			
}

