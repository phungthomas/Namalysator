#ifndef _REPORT_W_H
#define _REPORT_W_H

#include <QtGui>
#include "dbrequest.h"


class w_report : public QWidget
{
    Q_OBJECT

public:
	w_report(QWidget *parent = 0);
	~w_report();

	void init();

	void setValue(int i, int tot);
	void setBatchDetail();


private:
	QLabel* labCheckCount;
	QLabel* labTot;
	QLabel* report;
	dbrequest db;
	
};

#endif
