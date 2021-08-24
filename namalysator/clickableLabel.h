#pragma once

#include <QLabel>
class clickableLabel : public QLabel {
	Q_OBJECT
public:
	clickableLabel(const QString& text, QWidget* parent = 0);
	clickableLabel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
	~clickableLabel() {}
signals:
	void clicked();
	void rightClicked();
public slots:
	void slotClicked();
	void slotRightClicked();
protected:
	void mousePressEvent(QMouseEvent* event);
};