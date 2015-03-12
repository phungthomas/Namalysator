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

	void init();
	void setBatchDetail();


private:
	dbrequest db;
};

#endif