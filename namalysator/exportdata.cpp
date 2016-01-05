#include "exportdata.h"
#include <fstream>
#include <QDate>
#include "metsoutput.h"

void exportdata::writeToExcel(BatchDetail detail)
{
}

void exportdata::writeSummary(odswriter *ow, BatchDetail *bdetail,dbrequest *db)
{
	QString ss;

	ow->open_sheet("Summary");
	ow->open_row();
	ow->add_text("Summary of disk");
	ow->add_text(bdetail->batchName);
	
	ow->close_row();	ow->open_row();
	ow->add_text("Date of test");
	ow->add_text(bdetail->testDate);
	ow->close_row();
	
	ow->open_row();
	ow->close_row();
	
	ow->open_row();
	ow->add_text("Number of Mets files");
	ow->add_text(ss.setNum(bdetail->count).toStdString());
	ow->close_row();
		
	ow->open_row();	ow->close_row();
	
	ow->open_row();	
	ow->add_text("Year");
	ow->add_text("Number of Issues");
	ow->add_text("Number of Supplements");	
	ow->close_row();
	
	std::map<int,std::pair<int,int>>mapYearCount  = db->getSumMetsYear(bdetail->idTestSet);
	for(std::map<int,std::pair<int,int>>::iterator it = mapYearCount.begin(); it != mapYearCount.end(); it++)
	{
	
		ow->open_row();	
		ow->add_number(it->first);
		ow->add_number(it->second.first);
		ow->add_number(it->second.second);
		ow->close_row();
	}
	
	ow->open_row();	
	ow->close_row();	
	ow->open_row();
	ow->add_text("Severity");
	ow->add_text("Error Category");
	ow->add_text("Count");
	ow->add_text("Number of issues affected");
	ow->add_text("Percentage issues affected");
	ow->add_text("Details on sheet");		
	ow->close_row();
	std::vector<ErrorSummary> vEs = db->getvErrorSummary(bdetail->idTestSet);
	
	 for(size_t i=0;i < vEs.size();i++)
	 {
		int countErrorMets = db->getcountMetsErrorForEachErrorType(bdetail->idTestSet,vEs[i].errorType.id);
		ow->open_row();			 
		ow->add_text(vEs[i].errorType.severity.gravity);
		ow->add_text(vEs[i].errorType.error);
		ow->add_number(vEs[i].count);
		ow->add_number(countErrorMets);		
		float percentage = float(vEs[i].count) / float(bdetail->count) *100 ;		
		ow->add_number(percentage);		
		ow->add_text(vEs[i].errorType.category.name);
		ow->close_row();
	 }	
	ow->close_sheet();	
}

void exportdata::writeCatError(odswriter *ow, BatchDetail *bdetail,dbrequest *db)
{
	std::map<int,ErrorCategory> vErrorCat = db->getErrorCategory();
	for(std::map<int,ErrorCategory>::iterator it=vErrorCat.begin();it != vErrorCat.end() ;it ++)
	{	
		std::vector<MetsError> vSchemaE= db->getvErrorPerCategory(it->second.id_category,bdetail->idTestSet);
		if(vSchemaE.size()!=0)
		{
			ow->open_sheet(it->second.name);		
			ow->open_row();
			ow->add_text("Severity");
			ow->add_text("Type");
			ow->add_text("Location");
			ow->add_text("Message");
			ow->add_text("File");
			ow->add_text("Search for");
			ow->add_text("Year");
			ow->add_text("Ack");
			ow->close_row();
			
			for(size_t i =0;i < vSchemaE.size();i++)
			{
				ow->open_row();
				ow->add_text(vSchemaE[i].errorType.severity.gravity);
				ow->add_text(vSchemaE[i].errorType.error);
				ow->add_text(vSchemaE[i].filePart);
				ow->add_text(vSchemaE[i].message);
				ow->add_text_with_link(vSchemaE[i].mets.fileName, "file://" + bdetail->path + vSchemaE[i].filenameFullPath);
				ow->add_text(vSchemaE[i].id_search);
				ow->add_number(vSchemaE[i].mets.year);
				ow->add_text(vSchemaE[i].accepted==0?std::string("Not accepted"):std::string("Accepted"));
				ow->close_row();
			}
			ow->close_sheet();
		}
	}
}

exportdata::exportdata()
{
	
}

void exportdata::exportErrors(BatchDetail batchdetail,std::string fileName)
{
		odswriter ow;
	if (!ow.open_document(fileName)) 
	{
		return;     
	}		
	dbrequest db;
	db.setDataBaseName(batchdetail.database);	
	writeSummary(&ow,&batchdetail,&db);
	writeCatError(&ow,&batchdetail,&db);	
	exportDates(&ow,&batchdetail,&db);				
	ow.close_document();


}

void exportdata::exportDates(odswriter *ow, BatchDetail *bdetail,dbrequest *db)
{
	std::stringstream ss;
	std::vector<DateError> vError = db->getDateError(bdetail->idTestSet);
	
	ow->open_sheet("DATES");		
	ow->open_row();
	ow->add_text("Category");
	ow->add_text("Error");
	ow->add_text("Year");
	ow->add_text("Comment");
	ow->close_row();
	

	for (size_t i =0;i < vError.size();i++)
	{
		DateError dateError = vError[i];
		std::stringstream ss;
	
		ss << "Issue " << dateError.issues << " on ";
				
		QDate dateBegin = dateBegin.fromString(dateError.dateBegin.c_str(),"yyyy-MM-dd"); 
		QDate dateEnd = dateEnd.fromString(dateError.dateEnd.c_str(),"yyyy-MM-dd"); 			
	
		dateBegin = dateBegin.addDays(1);
		bool first =false;
		bool in = false;
	//	for (size_t j = dateBegin.toJulianDay();j < dateEnd.toJulianDay();j++)
		while ( dateBegin != dateEnd)
		{	
					
			if (dateBegin.dayOfWeek() ==7)
			{				
			//	j++;
			}
			else if (first ==false)
			{
				if (dateError.errortype.id == 22) //à changer par après
				{
					ss << dateEnd.toString("yyyy-MM-dd").toStdString();
					in = true;
					break;
					
				}
				else
				{
					ss << dateBegin.toString("yyyy-MM-dd").toStdString();					
				}				
				first = true;
				in = true;
			}
			else if (first == true)
			{
				ss << " to " << dateEnd.addDays(-1).toString("yyyy-MM-dd").toStdString();					
				in = true;
				break;
			}	
			dateBegin = dateBegin.addDays(1);			
		}		
		if (in ==false)
		{
			ss << dateEnd.toString("yyyy-MM-dd").toStdString();
		}
		ow->open_row();
		ow->add_text(dateError.errortype.error);
		ow->add_text(ss.str());		
		ow->add_number(dateEnd.year());

		if (dateError.dateComment.size()!=0)
		{
			for (size_t j=0;j< dateError.dateComment.size();j++)
			{			
				ow->add_text(dateError.dateComment[j].comment.c_str());	
			}
		}
		ow->close_row();		
	}
	ow->close_sheet();	
}


void exportdata::exportIssues(std::map<int,MetsFile> mapMets,std::string fileName)
{
	odswriter ow;
	if (!ow.open_document(fileName)) 
	{
		return;     
	}
	
	ow.open_sheet("Errors");	
	ow.open_row();
	ow.add_text("Jour");
	ow.add_text("Mois");
	ow.add_text("Annee");
	ow.add_text("Numero");
	ow.add_text("Pages");
	ow.add_text("Supplement");
	ow.add_text("S. pages");
	ow.add_text("Jg.");
	ow.add_text("Volume");
	
	
	ow.close_row();
	for (std::map<int,MetsFile>::iterator it = mapMets.begin(); it!= mapMets.end();it++)
	{	
		MetsFile *mets = &it->second;	
		ow.open_row();		
		ow.add_number(mets->date.day());
		ow.add_number(mets->date.month());
		ow.add_number(mets->date.year());
		
		std::stringstream ss;
		ss << "";
		for(size_t i =0;i< mets->vectIssueNumber.size();i++)
		{
			ss << mets->vectIssueNumber[i];
			if (mets->vectIssueNumber.size() > i+1)
				ss << " , ";
		}
		
		ow.add_text(ss.str());
		ow.add_number(mets->pages);
		std::string supplement_string;
		for (std::vector<std::string>::const_iterator it = mets->supplements.begin(); it != mets->supplements.end(); ++it) {
			if (!supplement_string.empty()) {
				supplement_string += " ; ";
			}
			supplement_string += *it;
		}
		ow.add_text(supplement_string);
		ow.add_text("");
		ow.add_text("");
		ow.add_text("moyen");		
		ow.close_row();				
	}	
		ow.close_sheet();
		ow.close_document();		
}