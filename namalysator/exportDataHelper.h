#ifndef EXPORTDATA_H____
#define EXPORTDATA_H____

#include <string>
#include <map>
#include <vector>
#include "structgui.h"
#include "dbrequest.h"

//+++ class exportDataHelper
// helper to create .ods file containing title sampling of news paper
//

class exportDataHelper{
public :
	void exportData(std::string filenameToCreate);
private:
	void findArticle(Item *item,std::string docType);
	void createArticle();
	void findBlockToArticle(Item *item, std::vector<typeBlock> &output);
	std::vector<Item*> vectItem;
	std::map<std::string,Article> mapArticleWithIdDiv;
	std::map<int,Article> mapArticle;
	dbrequest db;
};

#endif
