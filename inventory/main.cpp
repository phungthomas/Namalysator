#include "configparserinventaire.h"
#include "inventaireparser.h"
#include "insertinventaire.h"
#include "xmlparser.h"
#include <string>
#include <iostream>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"
#include <sstream>

namespace fs = boost::filesystem;

// Verify if the database does not exist, create a new database
bool existDatabase(sqlinventaire *db,std::string databasePath,std::string sqlCreateTablePath)
{	
	if ( !fs::exists(databasePath) )	
	{
		if (db->createTable(sqlCreateTablePath.c_str())==false)
		{							
			return false;
		}	
	}	
	return true;
}

int main()
{	
	//get current path of the folder
	fs::path CurrentPath( fs::initial_path<fs::path>());
	
	std::stringstream configPath,sqlCreateTablePath,logFilePath;	
	configPath << CurrentPath << "/inventaireconfig.xml"; 
	logFilePath << CurrentPath << "inventaireErrorLog.log"; 
	Inventaire inv;
	configparserinventaire config(&inv);
	
	
	FILE *fp;	
	//Parse the config file	
	if (ParseDocument(configPath.str().c_str(),&config) !=0 )	
	{				
		fopen_s(&fp,logFilePath.str().c_str(), "a");
		if (fp!=NULL)
		{
			fprintf(fp,"Could not parse config file %s\n",configPath.str().c_str());
				
		}
		fclose(fp);
		return 1;	
	}
	
	inventaireparser inventaire;
	//Parse the config file	
	if (ParseDocument(inv.input.c_str(),&inventaire) !=0 )	
	{		
		fopen_s(&fp,logFilePath.str().c_str(), "a");
		if (fp!=NULL)
		{
			fprintf(fp,"Could not parse inventaire file %s\n",inv.input.c_str());				
		}
		fclose(fp);					
		
		return 2;
	}
		
	sqlCreateTablePath << CurrentPath << "/createTableInventaire.txt";

	
	std::string datab = inv.database + ".db";	
	std::map<std::string,std::vector<info_t> > mapInventaire = inventaire.getMapInventaire();	
		
	sqlinventaire db(inv.code,inv.name,datab,&mapInventaire);
	if (!existDatabase(&db,datab,sqlCreateTablePath.str()))
	{	
		fopen_s(&fp,logFilePath.str().c_str(), "a");
		if (fp!=NULL)
		{
			fprintf(fp,"Could not parse sqlCreateTablePath file %s\n",sqlCreateTablePath.str().c_str());
		}
		fclose(fp);		
	
		return 3;
	}
	db.openDB();	
	db.insertInventaire();		
	return 0;	
}