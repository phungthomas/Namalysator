#ifndef GUI_UTILITIES_H_
#define GUI_UTILITIES_H_
#include <string>
#include <vector>
#include <direct.h> // for getcwd
#include <stdlib.h>// for MAX_PATH
#include "structgui.h"
#include <QDate>
#include "../common_files/utilities.h"

std::vector<int> getIssueNumber(const std::string &issueNumber);
std::vector<int> getIssueNumberExcel(const std::string &issueNumber);
bool createdir(const std::string dir);
std::string convertToStringIssueNumber(std::vector<int> vIssueNumber);
std::string messageMisisngIssue(DateError dateError);

#endif //GUI_UTILITIES_H_