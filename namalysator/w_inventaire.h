#ifndef W_INVENTAIRE_H
#define W_INVENTAIRE_H

#include <QtGui>

#include "structgui.h"
#include "dbrequest.h"
#include <map>

namespace Ui
{
    class w_inventaire;
}
//! implementation of functions for working with the inventory
class w_inventaire : public QWidget
{
    Q_OBJECT

public:
    w_inventaire(QWidget *parent = 0);
    ~w_inventaire();
	void setBatchDetail(const BatchDetail &d);
private:
    Ui::w_inventaire *ui;  	
    dbrequest db;
    dbrequest dbInventaire;
    BatchDetail batch;
    MetsFile mets,currentMets;
    QStringList labels,labelInventaire,labelInventaireTotal;   
    QTableWidget *widgetInventaire;
	bool changeNewDate;
    std::vector<Excel> vInventaire;   
    std::map<QDate,std::vector<Excel> > mapInventaire ;
    void compare();
    void fillMetsfromTestset(std::map<int,MetsFile> mapMets);
    void fillMetsfromInventory(QTableWidget *widget);
    void compareDate(std::map<int,MetsFile> mapMets);
    bool compareIssueNumber(MetsFile *mets,int currentLine);
    void fillComboYear();
   //! fill combobox of years
    void createConnections();
   
    void fillNotReferencedissues();
    std::map<int,MetsFile> mapErrorMets;
    std::vector<MetsFile> vErrorMets;
    std::vector<MetsFile> vNotReferencedMets;
    
  private slots: 
	void lineChanged(QTableWidgetItem *,QTableWidgetItem *);
	void viewIssue();
	void showInventaire();
	void getcbYear(QString);
	void exportIssues();   
	void showErrors();
};

#endif // W_INVENTAIRE_H
