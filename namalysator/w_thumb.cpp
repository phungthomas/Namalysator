#include "w_thumb.h"
#include <sstream>
#include <iomanip>


void w_thumb::cancel(){
	canceled = true;
}

void w_thumb::perform(){
	QPushButton* _but;
	QImage image;
	QImage imagebis;

	stepi++;
	int i = stepi;

	
		emit nextValue(i);
		std::stringstream ss;
        int jj=i%56;

		ss<< "C:\\SmallTestBook\\243149\\tif\\" << std::setfill('0')<<std::setw(5)<< jj << ".tif";
		//ss<< "E:\\tif\\" << std::setfill('0')<<std::setw(5)<< jj << ".tif";
		emit newText(ss.str().c_str());
		image.load(ss.str().c_str());
		;

		//QIcon icon(ss.str().c_str());
		_but = new QPushButton();
		_but ->setMinimumSize(200,200);
		_but ->setMaximumSize(370,370);
		_but ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		_but ->setToolTip(ss.str().c_str());
		_but ->setIcon(QPixmap::fromImage(image.scaled(200,200,Qt::KeepAspectRatio,
			           Qt::SmoothTransformation /*Qt::FastTransformation*/),
					   Qt::DiffuseAlphaDither|Qt::ColorOnly));
		_but ->setIconSize(QSize(200,200));
		

		 QPixmapCache::clear();
		
		
		addInternal(_but);
		
	
}

void w_thumb::load(){
	canceled = false;
	stepi = 0;
	QProgressDialog dlg;
	dlg.setWindowTitle("Loading thumbnail");
	dlg.setRange(0, 144); // number max of page

	QTimer timer;
 
	QObject::connect(this, SIGNAL(nextValue(int)), &dlg, SLOT(setValue(int)));
	QObject::connect(this, SIGNAL(newText(QString)), &dlg, SLOT(setLabelText(QString)));
	QObject::connect(&dlg, SIGNAL(canceled()), this, SLOT(cancel()));
	connect(&timer, SIGNAL(timeout()), this, SLOT(perform()));

	dlg.show();
	timer.start();
	dlg.exec (); // local loop of event 
}

void w_thumb::init(){
	count=0;
	_mainLayout = new QVBoxLayout();
	this->setLayout(_mainLayout);
	_sbar = new QScrollArea();
	_sbar->setMinimumSize(QSize(1320,800));
	_sbar->setMaximumSize(QSize(19000,19000));
	_sbar->resize(this->frameSize());	
	_sbar->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
	_sbar->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	_sbar->setWidgetResizable(false);
	_mainLayout->addWidget(_sbar);

	QWidget* internal = new QWidget();
    
	
	//_sbar.setGeometry(QRect(0, 0, 937, 817));
	_qvLayout = new QVBoxLayout();
	_qvLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	_qvLayout->setSpacing(1);
	
	currentLayout = new QHBoxLayout();
	_qvLayout->addLayout(currentLayout);
	
	//curr = &_qvLayout;

	internal->setLayout(_qvLayout);
	internal->setMinimumWidth(1200);
	internal->setMinimumHeight(4800);
	internal->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

	_sbar->setWidget(internal);
	show();
	load();
}
void w_thumb::addInternal(QWidget * wid){
	currentLayout->addWidget(wid);
	count ++;
	if ( count == 6 ) {
		count = 0;
		currentLayout = new QHBoxLayout();
		_qvLayout->addLayout(currentLayout);
	}
}

w_thumb::w_thumb(QWidget *parent):QWidget(parent){
	init();
}

w_thumb::~w_thumb(){
}