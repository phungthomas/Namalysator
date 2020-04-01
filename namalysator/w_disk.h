#ifndef W_DISK_H
#define W_DISK_H

#include <QWidget>
#include <QDirModel>
#include <QtWidgets>
#include<QListWidget>
#include<QListWidgetItem>
#include "structgui.h"
#include <map>
#include <vector>
#include "dbrequest.h"
#include "w_calendar.h"

namespace Ui {
    class w_disk;
}

class w_disk : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(w_disk)
public:
    explicit w_disk(QWidget *parent = 0);
    virtual ~w_disk();    
    void setBatchDetail();
    bool initHeader(const MetsFile &mets);
    void initDetails(const MetsFile &mets);
    dbrequest db;
    
protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::w_disk *m_ui;
	void w_disk::createConnections();	
	void clearDetails();
	QDirModel model;	
	QListWidgetItem *lst;   
    QStringList labels;
    //BatchDetail batch;
	std::map<int, MetsFile> listOfMetsOnDay;
    
private slots :
	void clickDate(QDate);  
	void openPath(QModelIndex);
	void getIdMets(QListWidgetItem*);
};

#endif // W_DISK_H
