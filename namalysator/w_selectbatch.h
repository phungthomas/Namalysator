#ifndef W_SELECTBATCH_H
#define W_SELECTBATCH_H

#include <QtGui/QWidget>
#include<QListWidget>
#include<QListWidgetItem>
#include "dbrequest.h"
#include "structgui.h"
#include <map>

namespace Ui {
    class w_selectBatch;
}

//! The functions for the selection of a batch are implemented here
class w_selectBatch : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(w_selectBatch)
public:
    explicit w_selectBatch(QWidget *parent = 0);
    virtual ~w_selectBatch();

protected:
    virtual void changeEvent(QEvent *e);  
	void createConnections();	
    void fillItemBatchName();
    void fillItemInventaire();
    void fillBatchDetail();
    void clearBatchDetail();
    void loadParameters(int id);
    void loadParametersCompareBatch();
    bool inputDisk();
private : 
	Ui::w_selectBatch *m_ui;
    std::vector<Inventaire> vInventaire ;   
    dbrequest db; 
    dbrequest dbInventaire; 
    BatchDetail& batch;
    Inventaire inv;   

signals:
	void validated(std::string);
	void exited();
    
protected slots:
	void getListDate(QString date); 
	void getMets(QListWidgetItem*);
	void valider();
	void browsePath();
	void browseDb();
	void exit();     
    void browsePathInventaire();
};

#endif // W_SELECTBATCH_H
