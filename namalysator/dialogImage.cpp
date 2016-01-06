#include "dialogImage.h"


DialogImage::DialogImage(QWidget *parent){
	layout = new QVBoxLayout;
	image = new QLabel();

	init();
}

DialogImage::~DialogImage(){

}

void DialogImage::init(){
	layout->addWidget(image);
	this->setLayout(layout);
}

void DialogImage::setQImage(QImage& icon){
	image->setPixmap(QPixmap::fromImage(icon.scaled(250,250,Qt::KeepAspectRatio,
		           Qt::SmoothTransformation /*Qt::FastTransformation*/),
				   Qt::DiffuseAlphaDither|Qt::ColorOnly));

	this->show();
	this->adjustSize();
    this->raise();
}
