#ifndef W_THUMB_H
#define W_THUMB_H

#include <QtWidgets>
#include <QPushButton>
#include <QScrollArea>
#include <QProgressDialog>
#include <vector>
#include "flowlayout.h"
#include "structgui.h"

class InternalQPushButton : public QPushButton{
	 Q_OBJECT

public:

	InternalQPushButton(QWidget *parent = 0);
	virtual ~InternalQPushButton();

    int pageNb;
public slots:
	void onclick();
	
signals:
	void clickedPageNb(int i);

};


class w_thumb : public QWidget
{
    Q_OBJECT

public:
	w_thumb(int,QWidget *parent = 0);
	w_thumb(std::string _path, std::map<int,LinkedFiles> _listFile,QWidget *parent = 0);
	~w_thumb();

	void load();
public slots:
	void cancel();
	void perform();
	void onPage(int);

signals:
	void newText(QString);
	void nextValue(int i);
	void selectPage(int i);

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
	std::vector<InternalQPushButton*> allButton;
	std::map<int,LinkedFiles> listFile;
	std::string path; 
};

#endif
