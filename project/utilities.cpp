#include "../common_files/utilities.h"
#include <string.h>
#include <iostream>
#include <string>
#include <direct.h>
#include <sstream>
#include "metsverifier.h"

const char* get_named_attr(const char *name, const char **atts)
{
	const char *val = 0;
	if (!atts) {
		return 0;
	}
	while (*atts) {
		if (strcmp(*atts, name) == 0) {
			++atts;
			if (*atts) {
				val = *atts;
			}
			return val;
		} else {
			++atts;
			++atts;
		}
	}
	return val;
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


std::vector<int> getIssueNumber(const std::string &issueNumber)
{
	std::vector<int> result;
	// issue_numbers (take every single number behind n°)
	static const char sz_find[4] = {110, -62, -80, 0}; // 0x6E, 0xC2, 0xB0  This is n° in UTF-8
	std::string::size_type p = issueNumber.find(sz_find);
	//std::string::size_type p = issueNumber.find("n°");
	char lastspacer = 0;
	if (p != std::string::npos) {
		const char *c = issueNumber.c_str() + p;
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
	} else 
	{
		result.push_back(1);
	}
	return result;
}

std::string slash_path(std::string message)
{
	size_t j;	
	std::string str2 ("\\"); 
	
	for ( ; (j = message.find( str2 )) != std::string::npos ; ) 
	{	
		message.replace( j, str2.length(), "/" );	
	}
	return message;
}

std::string dump_alto_rect2str(const Block &r)
{
	std::stringstream os;
	os << r.vpos << "," << r.hpos<< " (" << r.vpos + r.height  << "," <<r.hpos + r.width << ")";
	return os.str();
}

const char *safe_sqlite3_column_text(sqlite3_stmt *pStmt, int iCol)
{
	static const char *g_sz_empty = "";
	const char *res = (const char *) sqlite3_column_text(pStmt, iCol);
	if (res) {
		return res;
	} else {
		return g_sz_empty;
	}
}
