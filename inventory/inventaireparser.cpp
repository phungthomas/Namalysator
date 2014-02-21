#include "inventaireparser.h"
#include "../common_files/xmltostr.h"
#include <iostream>
#include <sstream>


inventaireparser::inventaireparser()
{	
		state = root;
		isInHeader = false;
		isAnnexes = false;		
}

bool inventaireparser::is_row_data()
/* 
Assumptions v1:
  column 1 is a year
  column 2 is non-empty (issue number)
  column 6 is a single letter (layout type) - NOT USED
  column 7 is a numeral (volume)
Assumptions v2:
  (column 1 is day, column 2 is month)
  column 3 is year
  column 4 is non-empty (issue number)
  column 5 is number of pages
  column 7 is number of supplement pages (5+7 > 0)
  column 8 is layout type
  
*/
{
/*
for( size_t i=0;i < info.cells.size();i++)
{
	std::cout << info.cells[i] << ", " ;
} 
std::cout << std::endl;
*/

	if ( isInHeader == true)
	{
	
	std::stringstream ss;
		for( size_t i=0;i < info.cells.size();i++)
		{
			ss << info.cells[i] << ", " ;
		} 
		info.header = ss.str();
	}

	if (isAnnexes == true)	info.cells.push_back("1");
	else	info.cells.push_back("0");
	
	
	
	if (info.cells.size() >= 7) {
		if (info.cells[2].length() == 4) { // 4 digits in year
			int year = atoi(info.cells[2].c_str());
			if (year >= 1600 && year <= 2050) {
			
				int p = 0, sp = 0;
				if (info.cells[4].length() > 0) {
					p = atoi(info.cells[4].c_str());
				}
				if (info.cells[6].length() > 0) {
					sp = atoi(info.cells[6].c_str());
				}
				if (p + sp > 0) 
				{
					info.cells.push_back("1");
					return true;
				}
				else
				{
					info.cells.push_back("0");
					return true;
				}			
			}
		}
	}
	return false;
}

void inventaireparser::XMLstartElement(const char *name, const char **atts)
{	
	if (state == root) {
		if (strcmp(name, "Worksheet") == 0) {
			info.clear();
			isInHeader = true;
			const char *val = get_named_attr("ss:Name", atts);
			if (val) {
				info.sheetname = val;
			}
			state = sheet;
		}
	} else if (state == sheet) {
		if (strcmp(name, "Row") == 0) {
			state = row;			
			info.cells.clear();
		}
	} else if (state == row) {
		if (strcmp(name, "Cell") == 0) {
			state = cell;
			const char *val = get_named_attr("ss:Index", atts);
			if (val) {
				size_t n = atoi(val);
				while (info.cells.size() < n) {
					info.cells.push_back("");
				}
			} else {
				info.cells.push_back("");
			}
		}
	}
}
void inventaireparser::dump_row()
{
	// printf("\"%s\",", info.sheetname.c_str());
	size_t i;
	for (i = 0; i < info.cells.size(); ++i) {
		printf("\"");
		for (std::string::iterator it = info.cells[i].begin(); it != info.cells[i].end(); ++it) {
			if (*it == '"') {
				printf("\"\"");
			} else if (*it == 13 || *it == 10) {
			} else {
				printf("%c", *it);
			}
		}
		printf("\"");
		if ((i + 1 < info.cells.size()) || (i + 1 < ncols)) {
			printf(",");
		}
	}
	while (i < ncols) {
		printf("\"\"");
		if (i + 1 < ncols) {
			printf(",");
		}
		++i;
	}
	printf("\n");
}

void inventaireparser::XMLendElement(const char *name)
{		
		if (state == sheet) {
		if (strcmp(name, "Worksheet") == 0) {
			state = root;	
			isAnnexes = false;						
			mapInventaire[info.sheetname] = vInfo;			
			vInfo.clear();
		}
	} else if (state == row) {
		if (strcmp(name, "Row") == 0) 
		{
	
		if (is_row_data()) 
		{					
			vInfo.push_back(info);
		}
			state = sheet;
			isInHeader = false;
		}
	} else if (state == cell) {
		if (strcmp(name, "Cell") == 0) {
			state = row;
		}
	}
}

void inventaireparser::XMLcharacterData(const char *s, int len)
{	
	if (state == cell)
	{
		if (strcmp(std::string(s, len).c_str(), "ANNEXES") == 0)
		{				
			isAnnexes = true;	
		}
		info.cells.back().append(std::string(s, len));
	}
}



std::map<std::string,std::vector<info_t> > inventaireparser::getMapInventaire()
{

return mapInventaire;
}