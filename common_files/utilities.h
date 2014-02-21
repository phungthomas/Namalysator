#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <string>
#include <vector>
#include "struct.h"
#include "sqlite3.h"
const char *get_named_attr(const char *name, const char **atts);

std::string initializeXmlValidator();
std::string replaceApostrophe(std::string message);
std::vector<int> getIssueNumber(const std::string &s);
std::string slash_path(std::string path);
std::string dump_alto_rect2str(const Block &r);
const char *safe_sqlite3_column_text(sqlite3_stmt *pStmt, int iCol);

#endif //UTILITIES_H_
