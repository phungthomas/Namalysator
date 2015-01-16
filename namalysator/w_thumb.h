#ifndef W_THUMB_H
#define W_THUMB_H

#include <QtGui>
#include <QPushButton>
#include <QScrollArea>
#include <vector>
#include "flowlayout.h"

class w_thumb : public QWidget
{
    Q_OBJECT

public:
	w_thumb(int,QWidget *parent = 0);
	~w_thumb();

	void load();
public slots:
	void cancel();
	void perform();

signals:
	void newText(QString);
	void nextValue(int i);

private:
	void init();
	void createButton();
	void addInternal(QWidget *);
	QVBoxLayout* _mainLayout;
	QScrollArea* _sbar;
	QWidget* internal;
	QVBoxLayout* _qvLayout;
	//QHBoxLayout* currentLayout;
	FlowLayout* currentLayout;
    QPushButton _button;
	QProgressDialog* dlg;
	QTimer* timer;
	int count;
	bool canceled; 
	int stepi;
	int nbPage;
	std::vector<QPushButton*> allButton;
};

#endif
