#ifndef W_TITLECHECK_H
#define W_TITLECHECK_H

#include <QtGui>
#include "dbrequest.h"
#include "structgui.h"
#include <set>
#include "metsoutput.h"
namespace Ui {
    class w_titlecheck;
}

class w_titlecheck : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(w_titlecheck)
public:
    explicit w_titlecheck(QWidget *parent = 0);
    virtual ~w_titlecheck();
      void setBatchDetail(const BatchDetail &d);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::w_titlecheck *m_ui;       
	
    dbrequest db;
    BatchDetail batchdetail;
    std::set<std::string> to_extract;
    void createConnections();
    MetsFile mets;
    QListWidgetItem *lst;	
	QTreeWidgetItem *currentWidget; 
	QTreeWidgetItem *a;
    std::map<int,MetsFile> mapMets;       
    std::vector<Item*> vectItem;
	std::map<int,Article> mapArticle;
	std::map<std::string,Article> mapArticleWithIdDiv;
	std::set<std::pair<std::string ,QTreeWidgetItem*>> listItem;
	std::set<std::pair<std::string, std::string>> blockAltoDmd;	
	void createArticle();
    void findBlockToArticle(Item *item, std::vector<typeBlock> &output);
    void createAltoDmd();
    void findArticle(Item *item);
    int niveau;
    void checktitle();
    std::vector<QImage> vImage;
    void updateSummaryTitleError(); 
    std::vector<Title> vTitle;
private slots : 
	void save();
	void load();
	void reduceSize();
	void originalSize();
	void exportData();
};

#endif // W_TITLECHECK_H
