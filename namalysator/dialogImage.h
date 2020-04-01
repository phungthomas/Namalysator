#ifndef W_DIALOGIMAGE_H
#define W_DIALOGIMAGE_H


#include <QtWidgets>
#include <QImage>
#include <QLabel>
#include <QVBoxLayout>

class DialogImage : public QWidget
{
	Q_OBJECT

	public :
		DialogImage(QWidget *parent = 0);
		~DialogImage();

		void setQImage(QImage&);

	private :
		QVBoxLayout* layout;
		QLabel* image;

		void init();

};
#endif