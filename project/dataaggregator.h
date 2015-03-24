#ifndef DATAAGGREGATOR_H_
#define DATAAGGREGATOR_H_

#include "datafactory.h"
#include "../common_files/struct.h"
#include <set>
#include "sql.h" 

//! create structs for future verification
class dataaggregator{

private:
	database & db;
	std::string typeDocument;
	datafactory *dfTemp;
	Item *currentItem;
	Item *rootItem;
	std::vector<Item*> vectItem;
	std::vector<typeBlock> vectTypeBlock;
	DivType divType;
	std::string fileName;
public:
	dataaggregator(datafactory *df,std::string fname,database& _db,std::string _typeDocument);
	
private:	
	void transform();
	void findArticle(Item *item);
	void createArticleFactory();
	void findBlockToArticle(Item *item);
	void findDiv(Item *item);
	void createFactoryDivType();
	void deleteCurrentItem();
	void createGroupId();
	void createIssue();
};

#endif // DATAAGGREGATOR_H_