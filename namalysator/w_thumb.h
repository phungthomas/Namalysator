#ifndef W_THUMB_H
#define W_THUMB_H

#include <QtGui>
#include <QPushButton>
#include <QScrollArea>

class w_thumb : public QWidget
{
    Q_OBJECT

public:
	w_thumb(QWidget *parent = 0);
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
	void addInternal(QWidget *);
	QVBoxLayout* _mainLayout;
	QScrollArea* _sbar;
	QVBoxLayout* _qvLayout;
	QHBoxLayout* currentLayout;
    QPushButton _button;
	int count;
	bool canceled; 
	int stepi;

};

#endif
