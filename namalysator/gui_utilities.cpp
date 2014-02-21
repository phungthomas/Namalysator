#include "gui_utilities.h"
#include <stdio.h>
#include <sstream>
bool endline = false;

std::vector<int> getIssueNumberExcel(const std::string &issueNumber)
{
	std::vector<int> result;
	char lastspacer = 0;
	const char *c = issueNumber.c_str();
	int v = 0;
	while (*c) {
		if (*c >= '0' && *c <= '9') {
			v *= 10;
			v += *c - '0';
		} else {
			if (v > 0) {
				if (lastspacer == '-') { // handle a range
					if (!result.empty()) {
						if (v - result.back() > 0 && v - result.back() < 10) {
							for (int i = result.back() + 1; i < v; ++i) {
								result.push_back(i);
							}
						}
					}
				}
				result.push_back(v);
				lastspacer = 0;
			}
			if (*c == '-') {
				lastspacer = '-';
			}
			v = 0;
		}
		++c;
	}
	if (v > 0) {
		if (lastspacer == '-') { // handle a range
			if (!result.empty()) {
				if (v - result.back() > 0 && v - result.back() < 10) {
					for (int i = result.back() + 1; i < v; ++i) {
						result.push_back(i);
					}
				}
			}
		}
		result.push_back(v);
	}
	return result;
}

std::string convertToStringIssueNumber(std::vector<int> vIssueNumber)
{
	std::stringstream issue;
	for (size_t i=0;i < vIssueNumber.size();i++)
	{
		issue << vIssueNumber[i];
		if (i != vIssueNumber.size()-1)
		issue << " , ";
	}
return  issue.str();
}

bool createdir(const std::string &output_dir)
{
	if (output_dir.empty()) {
		return true;
	}
	
	int ret = _mkdir(output_dir.c_str());
	if (ret != 0) {
		switch (errno) {
			case 17 :
			//	std::cout << "Directory already exists " << std::endl;
		//		g_err.add_message(err_major, "Directory creation", "Directory exists " + output_dir, true);
				return false;
				break;
			case 2 :
		//		std::cout << "Path was not found " << std::endl;
			//	g_err.add_message(err_major, "Directory creation", "Path was not found " + output_dir, true);
				return true;
				break;
			default :
		//		g_err.add_message(err_major, "Directory creation", "Unknown error " + output_dir, true);
				return false;
		}
	}
	return true;
}

std::string messageMisisngIssue(DateError dateError)
{
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
		
return ss.str();
}