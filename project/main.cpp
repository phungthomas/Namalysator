#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>


#include "../common_files/xmltostr.h"
#include "../common_files/utilities.h"

#include "diskparser.h"
#include <time.h>
#include <locale.h>
#include "metsparser.h"
#include "altoparser.h"
#include "sql.h"
#include "errorhandler.h"

#include <parserCheck.h>

#include "dataaggregator.h"
#include "verifytitles.h"
#include "verifyblocks.h"
#include "verifydivs.h"
#include "verifyidentifierinmix.h"
#include "verifyunlinkedidentifier.h"
#include "verifypdf.h"
#include "verifyalto.h"
#include "verifyimg.h"
#include "verifyblockstructure.h"
#include "verifydatemismatch.h"
#include "verifymissingissue.h"
#include "verifyinvalidsupplement.h"
#include "verifyinvalidissuenumber.h"
#include "verifynoissuedefined.h"
#include "verifyaltoblockperpage.h"
#include "verifycoveragepercentagealtoblocks.h"
#include "verifyoddspages.h"
#include "verifydatefolder.h"
#include "verifychecksum.h"
#include "verifycutouts.h"
#include "verifymeasurement.h"
#include "titletocheck.h"
#include "datehelper.h"
#include <configparser.h>
#include "metsverifier.h"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"

#include "../common_files/precisiontimer.h"

namespace fs = boost::filesystem;

//get the current date time
std::string getDate()
{
	char dateStr [20];
	char timeStr [9];
	_strdate_s(dateStr);
	std::string date =dateStr;	
	_strtime_s( timeStr );
	date = date + " " + timeStr;
	//std::cout << "The current time : " << date << std::endl;  	
	return  date;
}

// print to command line
void printCmd(std::string var)
{
	std::cout << var << std::endl;
}

// verify if the input path is correct
bool validInputPath(std::string path,errorHandler *hError)
{	
	 if ( !fs::exists(path) )
	 {
		hError->begin("The input directory " + path + "  does not exist ");				
		return false;
	 }
	 return true;	
}
// Verify if the database does not exist, create a new database
bool existDatabase(database *db,errorHandler *hError,std::string databasePath,std::string sqlCreateTablePath)
{	
	if ( !fs::exists(databasePath) )	
	{
		if (db->createTable(sqlCreateTablePath.c_str())==false)
		{	
			hError->begin("The sql file is missing");				
			return false;
		}	
	}	
	return true;
}

void initXSDMets(parserCheck*);
void initXSDAlto(parserCheck*);

int start()
{		
	
	//get current path of the folder
	fs::path CurrentPath( fs::initial_path<fs::path>());
	
	std::stringstream configPath,sqlCreateTablePath;	
	configPath << CurrentPath << "/config.xml"; 	

	Parameters *parameter = new Parameters;

	configparser config(parameter);
	//Parse the config file
	
	if (config.parse(configPath.str().c_str()) !=0 )	
	{	
		errorHandler hLog;		
		hLog.setlogFilePath("commonLog.log");		
		hLog.begin("Can not parse config file");
		hLog.begin(" return 1");	
		return 1;				
	}	

	std::string batchName = parameter->batchName;
	std::string datab = parameter->database + ".db";
	std::string input= parameter->input;		

	sqlCreateTablePath << CurrentPath << "/createtable.txt";
	
	std::stringstream logFilePath;
	logFilePath <<CurrentPath << "/logfiles/" <<  batchName << ".log";	
	
	bool logExist =true;
	int currentLog=2;
	while (logExist ==true)
	{		
		if ( !fs::exists(logFilePath.str()) )
		{			
			logExist = false;
			break;
		}
		else
		{
			logFilePath.str("");
			logFilePath.clear();
			logFilePath <<CurrentPath<< "/logfiles/" <<  batchName << "Test" << currentLog <<".log";
			currentLog++;
		}
	}	
	
	//create object database and the connections
	database db(batchName, datab, logFilePath.str());	
	
	errorHandler hError;		
	hError.setDatabase(&db);
	//set path of the log file
	hError.setlogFilePath(logFilePath.str());
	hError.begin(getDate());
	//verify input path of disk
	if (validInputPath(parameter->input,&hError)== false)
	{	
		hError.begin("return 2");			
		return 2;	
	}
	FILE *fpTimingLog = fopen("C:\\Data\\metsverifier-log.txt","w");
	precisiontimer pt(fpTimingLog);
	pt.Start();

	cerr << "Database File:" << datab << endl;
	cerr << "Log File:" << sqlCreateTablePath.str() << endl;

	//verify if the database exist or not
	if (!existDatabase(&db, &hError, datab, sqlCreateTablePath.str()))
	{
	    //if there's is an error occured with the database, the programm will exit.
	    hError.begin("return 3");	
		return 3;
	}
	pt.LogTime("Creating DB");
	db.openDB();
	
	if(db.insertTestSet(batchName,getDate()) ==false)
	{	
		hError.begin("Database Error : Can not insert new Testset");
		hError.begin("return 4");					
		return 4;
	}		
	//insert the parameters of verifiers into the database
	db.insertParameterVerifiers(parameter);	

	pt.LogTime("Inserting DB parameters");
	

	parserCheck metsParserCall;
	parserCheck altoParserCall;

	initXSDMets(&metsParserCall);
    initXSDAlto(&altoParserCall);

	metsParserCall.setErrorHandler(&hError);
	altoParserCall.setErrorHandler(&hError);

	//Get all METS files from input
	DiskParser dp(&hError);
	std::vector<std::pair<std::string,std::string> > vectorMets = dp.parseDisk(input);	
	
	pt.LogTime("Parsing disk");

	std::cout << "Total Mets File : " <<  vectorMets.size() << std::endl ;

	//Begin to parse Mets File
	for(size_t i=0;i < vectorMets.size();i++)
	{	
		pt.Start();
		bool parseError = false;		
		std::string currentMetsFile = vectorMets[i].first;	
		std::string currentMetsPath = vectorMets[i].second;				
		datafactory df;	
		std::stringstream tempMessage;
		tempMessage << getDate().c_str() << " - Begin to parse MetsFile : " << i+1 << " " << currentMetsFile;
		hError.begin(tempMessage.str());		
		std::cout << tempMessage.str() << std::endl;
		pt.LogTime("\tHousekeeping before mets parser");
		metsParser metsP(currentMetsFile,&hError, &df);
		pt.LogTime("METS Parser creation");
		db.insertMets(batchName,currentMetsPath,currentMetsFile);
		pt.LogTime("Insrting METS into DB");
		std::string parseString = currentMetsPath + "/" + currentMetsFile;
		
		metsParserCall.setContentHandler(&metsP);
		//std::cerr << "START Parsing" << std::endl;
		hError.setFilePart(currentMetsFile);
		hError.setRelatedType("METS");

		if ( metsParserCall.parse( parseString.c_str())!= 0){
            hError.getError(cat_xml_error,"METS",currentMetsFile, "Could not parse Mets file %s\n" + currentMetsFile ,currentMetsFile,"");
			// go to the next file : structure are not provide like the parser has stop
			cerr << "STOP immediately --> see trace in DB" << endl;
			parseError = true;
			return 1;
		};

		/*
		std::cerr << "Next One Parsing" << std::endl;

		if (ParseDocument(parseString.c_str(),&metsP) !=0 )	
		{						
			hError.getError(cat_xml_error,"METS",currentMetsFile, "Could not parse Mets file %s\n" + currentMetsFile ,currentMetsFile,"");
			parseError = true;			
		};
		*/

		

		//std::cerr << "Finish" << std::endl;

		pt.LogTime("Parsing METS file");
		//Parse all the Altos from Mets		
		File_Group *fg = 0;
		fg = df.get<File_Group>("ALTOGRP");
		if ( fg != NULL ){
			for(size_t j=0;j < fg->vect.size();j++)
			{	
				Type_File tf = fg->vect[j];				
				const std::string &path = currentMetsPath + tf.ref;	
				altoparser altoP(path,tf.id,&hError,&df);
				altoParserCall.setContentHandler(&altoP);

				if ( altoParserCall.parse(path.c_str()) != 0){
					hError.getError(cat_xml_error,"LINKEDFILES",tf.id, "Could not parse " + tf.ref ,tf.ref,"");		
					parseError = true;
				};

	
			}
		
		pt.LogTime("Parsing ALTO files");
		if (parameter->oddsPages =="1")
		{
			verifyoddspages(&hError,currentMetsFile,fg->vect.size());
		}
		}
		pt.LogTime("Verify Odds pages");
		if (parameter->checkFile =="1")
		{
			verifypdf(&df,&hError,currentMetsPath);
			pt.LogTime("Verify PDF");
			verifyalto(&df,&hError,currentMetsPath);		
			pt.LogTime("Verify ALTO");
			verifyimg(&df,&hError,currentMetsPath);									
			pt.LogTime("Verify Images");
		}

		// Do transformation of the data factory
		dataaggregator da(&df,currentMetsFile);	
		pt.LogTime("Creating dataagregator");
		
		if (parameter->dateFolderIssue =="1")
		{			
			verifydatefolder(&hError,currentMetsFile,currentMetsPath);		
			verifydatemismatch(	&hError,df.get<Mets>("METS"));				
		}	
		//Begin for the verifiers		
		if (parseError == false)
		{				
			if (parameter->checkSum =="1")
			{
				verifychecksum(&df,&hError,currentMetsFile,currentMetsPath);				
			}
			
			if (parameter->divs =="1")
			{
				verifydivs vd(&df,&hError,currentMetsFile);				
			}

			if (parameter->unlinkedIdentifier =="1")
			{
				verifyunlinkedidentifier(&df,&hError,currentMetsFile);				
			}

			if (parameter->identifierMix =="1")
			{
				verifyidentifierinmix(&df,&hError,currentMetsFile);				
			}

			if (parameter->altoblockPerPage =="1")
			{
				verifyaltoblockperpage(&df,&hError,currentMetsFile);				
			}

			if (parameter->blockStructure =="1")
			{
				verifyblockstructure(&df,&hError,currentMetsFile);				
			}

			if (parameter->coveragePercentAlto =="1")
			{
				verifycoveragepercentagealtoblocks(&df,&hError,currentMetsFile);				
			}

			if (parameter->multipleBlockUse =="1")
			{
				verifyblocks(&df,&hError,currentMetsFile);				
			}

			if (parameter->noIssueDefined =="1")
			{
				verifynoissuedefined(&df,&hError,currentMetsFile);		
			}

			if (parameter->invalidSupplement =="1")
			{
				verifyinvalidsupplement(&df,&hError,currentMetsFile);				
			}								
			if (parameter->issueNumber =="1")
			{
				verifyinvalidissuenumber(&df,&hError,currentMetsFile);
			}	
			if (parameter->measurementSTD == "1"){
				std::cerr << "ADDING measurement test" << std::endl;
				verifyMeasurement(&df,&hError,currentMetsFile);
			}
			
			verifycutouts(&df,&hError,currentMetsFile);
			titletocheck(&df,&hError,currentMetsFile);	
			verifytitles vt(&df,&hError,currentMetsFile);

			//*/			

#ifdef DEBUGPARAMETERS
			std::cout << "		Begin to insert data " <<std::endl;
#endif // DEBUG
		}
		pt.LogTime("All other verifiers");
		db.insertALLData(&df);
		pt.LogTime("Writing to DB");
#ifdef DEBUGPARAMETERS
		std::cout << "		Insert data finito " <<std::endl;
#endif // DEBUG		
	}
	
	//exit(0);
	fclose(fpTimingLog);
	verifymissingissue(&hError,&db);
	
	//TODO quand c'est 0 et empty string
	db.insertRandomTitle(atoi(parameter->checkTitle.c_str()));
	db.insertRandomMets(atoi(parameter->sampling.c_str()),vectorMets.size());	

	hError.begin(getDate());
	hError.begin("The End");
	db.closeDB();
	return 0;
}

int main(int argc, char** argv){

	XMLPlatformUtils::Initialize ();
	
	start ();

	XMLPlatformUtils::Terminate ();
}

void initXSDMets(parserCheck* p){
	p->addXSD("mets.xsd");
	p->addXSD("mods-3-2.xsd");
	p->addXSD("mods-3-3.xsd");
	p->addXSD("xlink.xsd");
	p->lockaddXSD();
}
void initXSDAlto(parserCheck* p){
    p->addXSD("alto-1-2.xsd");
	p->addXSD("alto-1-4.xsd");
	p->addXSD("nonexistingFile.xsd"); // Test Purpose 
	p->lockaddXSD();
}