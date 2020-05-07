#ifndef EXPORTDATA_H____
#define EXPORTDATA_H____

#include <QtWidgets>
#include <string>
#include <map>
#include <vector>
#include "structgui.h"
#include "dbrequest.h"
#include "metsoutput.h"

//+++ class exportDataHelper
// helper to create .ods file containing title sampling of news paper
//

class exportDataHelper:public QObject{
		 Q_OBJECT
public :
	void exportData(std::string filenameToCreate,QWidget *parent);
public slots:
	void cancel();
	void perform();

signals:
	void nextValue(int i);
	
private:
	void findArticle(Item *item,std::string docType);
	void createArticle();
	void findBlockToArticle(Item *item, std::vector<typeBlock> &output);
	std::vector<Item*> vectItem;
	std::map<std::string,Article> mapArticleWithIdDiv;
	std::map<int,Article> mapArticle;
	dbrequest db;


	bool cancelled;
	QProgressDialog* dlg;
	QTimer* timer;

	headcutter *hc;
	std::string currentAlto;
	std::string currentTif;
	std::vector<Title> vTitle;
	size_t ij;
};

#endif
