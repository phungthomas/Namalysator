#ifndef ENTITYCOUNT
#define ENTITYCOUNT

#include <QtGui>

#include "dbrequest.h"


class w_entitycount : public QWidget
{
    Q_OBJECT

public:
	w_entitycount(QWidget *parent = 0);
	~w_entitycount();

	void init(QMainWindow* _qmain);
	void setBatchDetail();


private:



	QMainWindow* qmain;
	QMenu* menu;
	dbrequest db;
private slots :	
	void exportToFile();
};

#endif