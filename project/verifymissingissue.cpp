#include "verifymissingissue.h"
#include "sql.h"
#include "../common_files/struct.h"
#include <sstream>

verifymissingissue::verifymissingissue(errorHandler *hError,database *db)
{
	std::set<int> setIssue;
	bool findDuplicateIssue = false;	
	std::vector<int> vYear = db->getAllYears();

	for( size_t i =0; i< vYear.size();i++)
	{
		before =0;	
		current=0;
		setIssue.clear();
		bool firstItem = true;			
		std::vector<std::pair<int, Mets> > vMets = db->vMetsYear(vYear[i]);	
		for (size_t j=0;j< vMets.size();j++)
		{
			Mets mets = vMets[j].second;
			for( size_t k = 0; k < mets.vectIssueNumber.size();k++)
			{
				current = mets.vectIssueNumber[k];	
				
				if (current > 1000)
				hError->getDateError(cat_invalidIssueNumber,"",mets.date,current+"","invalid issue number" + current);
		
				findDuplicateIssue = false;				
					
			if (setIssue.find(current)== setIssue.end())
			{			
				setIssue.insert(current);
			}
			else if (j>0 &&  mets.date != vMets[j-1].second.date )
			{
				std::stringstream message;	
				message << current ;				
				hError->getDateError(cat_duplicateIssue,"",mets.date,message.str(),"Duplicate issue " + current);			
				findDuplicateIssue = true;
			} 
					
			if (current-1 == before)
			{
										
			}
			else if (findDuplicateIssue ==false)				
				if (firstItem==true)
				{					
					std::stringstream missingNumber;					
					if (before +1 == current-1)
					{
						missingNumber << before +1;
					}
					else
					{	
						missingNumber << before +1 << " to " << current-1;
					}
					std::stringstream message;					
					message << "Missing issue number  " << missingNumber.str() << " before " << mets.fileName;
					std::stringstream firstdateofYear;												
					firstdateofYear << mets.year << "-01-01";
					hError->getDateError(cat_missingIssue,firstdateofYear.str(),mets.date,missingNumber.str(),message.str());							
				}
				else if(j >0 && mets.date != vMets[j-1].second.date)						
				{	
					std::stringstream missingNumber;					
					if (before +1 == current-1)
					{
						missingNumber << before +1;
					}
					else
					{	
						missingNumber << before +1 << " to " << current-1;
					}
					std::stringstream message;												
					message << "Missing issue number " << missingNumber.str() << " between " << vMets[j-1].second.date << " - " << mets.date;
					hError->getDateError(cat_missingIssue,vMets[j-1].second.date,mets.date,missingNumber.str(),message.str());
				}
				before = current;	
				firstItem = false;			
			}
		}	
	}
}

