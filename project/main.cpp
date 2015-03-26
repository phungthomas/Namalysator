#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>


#include "../common_files/xmltostr.h"
#include "../common_files/utilities.h"

#include "diskparser.h"
#include <time.h>
#include <locale.h>
#include "metsparser.h"
#include "altoparser.h"
#include "sql.h"
#include "errorhandler.h"
#include "transform.h"


#include <parserCheck.h>
#include "parameterMETS.h"

#include "dataaggregator.h"
#include "verifytitles.h"
#include "verifyblocks.h"
#include "verifyidentifierinmix.h"
#include "verifyunlinkedidentifier.h"
#include "verifyFile.h"
#include "verifyalto.h"
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
#include "verifybook.h"
#include "verifyEmptyMix.h"
#include "verifyFolder.h"
#include "titletocheck.h"
#include "datehelper.h"
#include <configparser.h>
#include "metsverifier.h"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"
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


int start()
{	
	srand(time(NULL));
	
	//get current path of the folder
	fs::path CurrentPath( fs::initial_path<fs::path>());
	
	std::stringstream configPath,sqlCreateTablePath;	
	configPath << CurrentPath << "/config.xml"; 	

	ParameterMETS parameter;

	configparser config(&parameter);
	//Parse the config file
	
	std::cerr << "Config file :" << configPath.str().c_str() << std::endl;

	if (config.parse(configPath.str().c_str()) !=0 )	
	{	
		errorHandler hLog;		
		hLog.setlogFilePath("commonLog.log");		
		hLog.begin("Can not parse config file");
		hLog.begin(" return 1");	
		return 1;				
	}	

	std::string batchName = parameter.getValue("batchName");
	std::string subbatchName = parameter.getValue("subbatchName");
	std::string datab = parameter.getValue("database") + ".db";
	std::string input= parameter.getValue("input");	

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
	if (validInputPath(input,&hError)== false)
	{	
		hError.begin("return 2");			
		return 2;	
	}
	std::stringstream fpFile ;
	fpFile.clear();
	fpFile<<CurrentPath<<"/metsverifier_TIME.log";
	FILE *fpTimingLog = fopen(fpFile.str().c_str(),"w");
	if ( fpTimingLog == NULL ){
		std::cerr << "Could not open :"<< fpFile.str() <<std::endl;
		std::cerr << "Emergency stop" << std::endl;
		return 3;
	}
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
	
	if(db.insertTestSet(batchName,subbatchName,getDate()) ==false)
	{	
		hError.begin("Database Error : Can not insert new Testset");
		hError.begin("return 4");					
		return 4;
	}		
	//insert the parameters of verifiers into the database
	db.insertParameterVerifiers(&parameter);	

	pt.LogTime("Inserting DB parameters");
	
	parserCheck* parserCheckBNLMono=parameter.getParser("BNLMonograph");
	parserCheck* parserCheckBNLSerial=parameter.getParser("BNLSerial");
	parserCheck* parserCheckBNLNews=parameter.getParser("BNLNewspaper");

	parserCheck* parserCheckBNL=0;
	parserCheck* metsParserCall=parameter.getParser("METS");
	parserCheck* altoParserCall=parameter.getParser("ALTO");

	metsParserCall->setErrorHandler(&hError);
	altoParserCall->setErrorHandler(&hError);

	//Get all METS files from input
	DiskParser dp(&hError);
	std::vector<std::pair<std::string,std::string> > vectorMets = dp.parseDisk(input);	
	
	pt.LogTime("Parsing disk");

	std::cout << "Total Mets File : " <<  vectorMets.size() << std::endl ;

	//Begin to parse Mets File
	for(size_t i=0;i < vectorMets.size();i++)
		//for ( int j=0;j <10 ;j++)
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
		metsParser metsP(currentMetsFile,currentMetsPath,&hError, &df);
		if (parameter.getValueCheck("semanticchecks.emptyMix") == 1){
			metsP.getContext().flagMix = true; // start parsing of mix part				
		}


		// for testing purpose
		if (parameter.getValueCheck("divCount") == 1){
			metsP.getContext().flagDivCount = true;
		}



		pt.LogTime("METS Parser creation");
		db.insertMets(batchName,currentMetsPath,currentMetsFile);
		pt.LogTime("Insrting METS into DB");
		std::string parseString = currentMetsPath + "/" + currentMetsFile;
		
		metsParserCall->setContentHandler(&metsP);
		//std::cerr << "START Parsing" << std::endl;
		hError.setFilePart(currentMetsFile);
		hError.setRelatedType("METS");

		if ( metsParserCall->parse( parseString.c_str())!= 0){
            hError.getError(cat_xml_error,"METS",currentMetsFile, "Could not parse Mets file %s\n" + currentMetsFile ,currentMetsFile,"");
			// go to the next file : structure are not provide like the parser has stop
			cerr << "STOP immediately --> see trace in DB" << endl;
			parseError = true;
			continue;
		};

		std::string outputDir = parameter.getValue("outputDir");
		std::string generatedFile = outputDir + "/GENERATED" + currentMetsFile;
		transformParser transformCH;
		transformCH.getContext().openFile(generatedFile);
		metsParserCall->setContentHandler(&transformCH);

		if ( metsParserCall->parse( parseString.c_str())!= 0){
			    // normally never go hear
				hError.getError(cat_xml_error,"METS",currentMetsFile, "Could not parse Mets file %s\n" + currentMetsFile ,currentMetsFile,"");
				continue;
		};

		transformCH.getContext().closeFile();


		if ( transformCH.getContext().typeIssue.compare ("Monograph")==0 ){
			parserCheckBNL = parserCheckBNLMono;
		}else if ( transformCH.getContext().typeIssue.compare ("Newspaper")==0 ){
			parserCheckBNL = parserCheckBNLNews;
		}else if ( transformCH.getContext().typeIssue.compare ("Serial")==0 ){
			parserCheckBNL = parserCheckBNLSerial;
		}else {
			hError.getError(cat_xml_error,"METS",currentMetsFile, "typeIssue not known [\"Monograph\",\"Newspaper\",\"Serial\"] " + transformCH.getContext().typeIssue ,currentMetsFile,"");
			continue; 
		}

		parserCheckBNL->setErrorHandler(&hError);

		if ( parserCheckBNL->parse( generatedFile.c_str())!= 0){
			cerr << "STOP immediately --> File"<< generatedFile.c_str() << endl; // TODO
			// skip this mets and go next one
			continue;
		};

		pt.LogTime("Parsing METS file");


		//Parse all the Altos from Mets		
		File_Group *fg = df.get<File_Group>("ALTOGRP");
		if ( fg != NULL ){
			for(size_t j=0;j < fg->vect.size();j++)
			{	
				Type_File tf = fg->vect[j];				
				const std::string &path = currentMetsPath + tf.ref;	
				altoparser altoP(path,tf.id,&hError,&df);
				altoParserCall->setContentHandler(&altoP);
				hError.setFilePart(path);
				hError.setRelatedType("LINKEDFILES");

				if ( altoParserCall->parse(path.c_str()) != 0){
					hError.getError(cat_xml_error,"LINKEDFILES",tf.id, "Could not parse " + tf.ref ,tf.ref,"");		
					parseError = true;
				};
			}

			hError.setFilePart(currentMetsFile);
			hError.setRelatedType("METS");
		
			pt.LogTime("Parsing ALTO files");
			if (parameter.getValueCheck("dataintegrity.oddsPages") == 1)
			{
				verifyoddspages(&hError,currentMetsFile,fg->vect.size());
			}
			pt.LogTime("Verify Odds pages");
		}
		

		static verifyBook vBook;
		vBook.check(parameter.getValueCheck("inventoryBook"),metsP.getContext());

		static verifyEmptyMix vMix;
		vMix.check(parameter.getValueCheck("semanticchecks.emptyMix"),metsP.getContext());

		static verifyFolder vFold;
		vFold.check(parameter.getValueCheck("semanticchecks.Folder"),metsP.getContext());

		if (parameter.getValueCheck("divCount") == 1){
			db.insertDivCount( metsP.getContext().divIDCount );
		};


		if (parameter.getValueCheck("dataintegrity.checkFile") == 1)
		{
			verifyFile(&df,&hError,currentMetsPath,"PDFGRP");
			pt.LogTime("Verify PDF");
			verifyalto(&df,&hError,currentMetsPath);		
			pt.LogTime("Verify ALTO");
			verifyFile(&df,&hError,currentMetsPath,"IMGGRP");						
			pt.LogTime("Verify Images");
			if (parameter.getValueCheck("dataintegrity.checkFilePNG") == 1){
				verifyFile(&df,&hError,currentMetsPath,"PNGGRP");						
				pt.LogTime("Verify PNG Images");
			}
		}

		// Do transformation of the data factory
		dataaggregator da(&df,currentMetsFile,db,metsP.getContext().papertype);	
		pt.LogTime("Creating dataagregator");
		
		if (parameter.getValueCheck("semanticchecks.dateFolderIssue") == 1)
		{			
			verifydatefolder(&hError,currentMetsFile,currentMetsPath);		
			verifydatemismatch(	&hError,df.get<Mets>("METS"));				
		}	
		//Begin for the verifiers		
		if (parseError == false)
		{				
			if (parameter.getValueCheck("dataintegrity.checkSum") == 1)
			{
				verifychecksum(&df,&hError,currentMetsFile,currentMetsPath);				
			}

			if (parameter.getValueCheck("dataintegrity.unlinkedIdentifier") == 1)
			{
				verifyunlinkedidentifier(&df,&hError,currentMetsFile);				
			}

			if (parameter.getValueCheck("semanticchecks.identifierMix") == 1)
			{
				verifyidentifierinmix(&df,&hError,currentMetsFile);				
			}

			if (parameter.getValueCheck("blocks.altoblockPerPage") == 1)
			{
				verifyaltoblockperpage(&df,&hError,currentMetsFile);				
			}

			if (parameter.getValueCheck("blocks.blockStructure") == 1)
			{
				verifyblockstructure(&df,&hError,currentMetsFile,parameter.getValueCheck("blocks.skipBlockInsidePrintSpace"));				
			}

			if (parameter.getValueCheck("blocks.coveragePercentAlto") == 1)
			{
				verifycoveragepercentagealtoblocks(&df,&hError,currentMetsFile);				
			}

			if (parameter.getValueCheck("blocks.multipleBlockUse") == 1)
			{
				verifyblocks(&df,&hError,currentMetsFile);				
			}

			if (parameter.getValueCheck("semanticchecks.noIssueDefined") == 1)
			{
				verifynoissuedefined(&df,&hError,currentMetsFile);		
			}

			if (parameter.getValueCheck("semanticchecks.invalidSupplement") == 1 )
			{
				verifyinvalidsupplement(&df,&hError,currentMetsFile);				
			}	

			//parameter.getValueCheck("semanticchecks.invalidSupplement.toto");// to show automatic parameter reporting

			if (parameter.getValue("issueNumber") == "1")
			{
				verifyinvalidissuenumber(&df,&hError,currentMetsFile);
			}	
			if (parameter.getValueCheck("blocks.measurementSTD") == 1){
				verifyMeasurement(&df,&hError,currentMetsFile);
			}
			
			verifycutouts(&df,&hError,currentMetsFile);
			titletocheck(&df,&hError,metsP.getContext(),db);
			verifytitles vt(&df,&hError,currentMetsFile);

			//*/			

#ifdef DEBUGPARAMETERS
			std::cout << "		Begin to insert data " <<std::endl;
#endif // DEBUG
		}
		pt.LogTime("All other verifiers");
		db.insertALLData(&df,metsP.getContext(),atoi(parameter.getValue("checkTitle").c_str()));
		pt.LogTime("Writing to DB");
#ifdef DEBUGPARAMETERS
		std::cout << "		Insert data finito " <<std::endl;
#endif // DEBUG		
	}
	
	//exit(0);
	fclose(fpTimingLog);
	if (parameter.getValueCheck("dates") == 1) {
		verifymissingissue(&hError,&db);
	}
	
	db.insertRandomMets(atoi(parameter.getValue("sampling").c_str()),vectorMets.size());	

	db.insertParameterVerifiers(&parameter); // for automatic reporting of test	

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