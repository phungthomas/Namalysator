#ifndef _BOOKLIST_H__
#define _BOOKLIST_H__

#include <QtGui>
#include "bookModel.h"
#include "bookColumn.h"
#include "dbrequest.h"

class w_booklist : public QWidget
{
    Q_OBJECT

public:
	w_booklist(dbrequest&,QWidget *parent = 0);
	~w_booklist();

	void init(bool);

	

public slots:
	void onclick(const QModelIndex &);


	void samplingSelection();
	void allSelection();


signals:
	void metsIdSelected(int i);
	void metsThumb(int i);


private:
	

	

	dbrequest& db;
	QVBoxLayout* _mainLayout;
	QTableView *bookView;
	bookModel *_bookModel;
	QSortFilterProxyModel * proxyModel;
};

#endif
