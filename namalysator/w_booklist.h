#ifndef _BOOKLIST_H__
#define _BOOKLIST_H__

#include <QtGui>
#include "bookModel.h"
#include "bookColumn.h"

class w_booklist : public QWidget
{
    Q_OBJECT

public:
	w_booklist(QWidget *parent = 0);
	~w_booklist();

private:
	void init();

	QVBoxLayout* _mainLayout;
	QTableView *bookView;
	bookModel *_bookModel;
	QSortFilterProxyModel * proxyModel;
};

#endif
