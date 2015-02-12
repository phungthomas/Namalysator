#include "w_screenshoterror.h"
#include "ui_w_screenshoterror.h"
#include <sstream>
#include "gui_utilities.h"



w_screenshoterror::w_screenshoterror(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::w_screenshoterror)
{
    m_ui->setupUi(this);
    createConnections();
    init();
    m_ui->label->setMouseTracking(true);
}

void w_screenshoterror::init()
{	
    clickCount =0;  
    point1X = 0;
    point1Y = 0;
    point2X = 0;
    point2Y = 0;
    currentColor = "Red";
    setBoxColor();
}
void w_screenshoterror::createConnections()
{
	connect(m_ui->btnSave,SIGNAL(clicked()),this,SLOT(saveError()));
    connect(m_ui->btnClearPainter,SIGNAL(clicked()),this,SLOT(clearPainter()));  
    connect(m_ui->btnColor,SIGNAL(clicked()),this,SLOT(setPenColor()));  
    connect(m_ui->btnClose,SIGNAL(clicked()),this,SLOT(close())); 
	connect(m_ui->comboBoxErrorType,SIGNAL(currentIndexChanged ( int )),this,SLOT(enableCustom(int)));
}

void w_screenshoterror::enableCustom(int i){

	bool flag = false;

	if ( m_ui->comboBoxErrorType->itemData(m_ui->comboBoxErrorType->currentIndex()).toInt() > -1 ){
		int id = vErrorType[m_ui->comboBoxErrorType->itemData(m_ui->comboBoxErrorType->currentIndex()).toInt()].id_type;
		if ( id == 100 ) {
			flag = true;
		}
		else{
			m_ui->customEdit->clear();
		}

	}


	m_ui->customEdit->setEnabled(flag);
	m_ui->label_2->setEnabled(flag);

}



w_screenshoterror::~w_screenshoterror()
{
    delete m_ui;
}

void w_screenshoterror::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void w_screenshoterror::close()
{
  this->~w_screenshoterror();

}

void w_screenshoterror::fillComboBoxErrortype()
{
	vErrorType = db.getErrorTypeCatStructure(mets.docType);
	m_ui->comboBoxErrorType->addItem("",-1); // false because db.saveStructError acess to vErrorTypee by the index of the comboBoxErrorType 
	                                        // otherwise correction must be made
	for (size_t i =0;i<vErrorType.size();i++)
	{	
		m_ui->comboBoxErrorType->addItem(vErrorType[i].error.c_str(),i);	
	}	
}


void w_screenshoterror::setBatchDetailImage(QPixmap pix,MetsFile m,w_structview *w, std::string _fileID)
{
	structView = w;
	//batchDetail = bd;
	fileID=_fileID;
	mets = m;	
	db.setDataBaseName(BatchDetail::getBatchDetail().database);  
	m_ui->comboBoxErrorType->clear();
	m_ui->customEdit->clear();
	m_ui->customEdit->setEnabled(false);
	m_ui->label_2->setEnabled(false);
	fillComboBoxErrortype();
	originalPixmap = pix;
	loadImage();
}

void w_screenshoterror::loadImage()
{
	pixmap = originalPixmap;
	m_ui->label->setPixmap(pixmap);
	m_ui->label->adjustSize();
}


void w_screenshoterror::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (clickCount ==0)
		{
			point1X = event->x();
			point1Y = event->y();
			clickCount =1;		
		}	
		else if (clickCount==1)
		{
			point2X = event->x();
			point2Y = event->y();
						
			QPainter painter(&pixmap);					
		//	painter.begin(&pixmap);
		//	QBrush b1( Qt::red );
		//	painter.setBrush( b1 );
			painter.setBrush(Qt::NoBrush);
			painter.setOpacity(5);
			painter.setPen(currentColor);
			
		
			x = point1X ;
			y = point1Y;
			width = point2X- point1X;
			height = point2Y-point1Y;
		
			painter.drawRect( x,y, width,height);
			
			clickCount=0;		
			m_ui->label->setPixmap(pixmap);
		//	m_ui->scrollArea->setWidget(m_ui->label);
		}	
	}
}





void w_screenshoterror::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		point2X = event->x();
		point2Y = event->y();
										
		QPainter painter(&pixmap);		
		painter.setBrush(Qt::NoBrush);
		painter.setOpacity(5);
		painter.setPen(currentColor);		
		x = point1X ;
		y = point1Y;
		width = point2X- point1X;
		height = point2Y-point1Y;		
		painter.drawRect( x,y, width,height);			
		clickCount=0;		
		m_ui->label->setPixmap(pixmap);
	}
}

void w_screenshoterror::clearPainter()
{ 
	pixmap = originalPixmap;
	m_ui->label->setPixmap(pixmap);
} 

 
void w_screenshoterror::saveError()
{	
	if ( m_ui->comboBoxErrorType->currentIndex()==0)
	{
		QMessageBox::information(this, tr("Missing Error"),
                                   tr("Please select an error"));	
	}
	else if (m_ui->txtCommentaire->toPlainText() == "" )
	{
		QMessageBox::information(this, tr("Missing message"),
                                   tr("Please insert a comment"));	
	}
	else
	{
		std::vector<StructureError> vStructureError = db.getStructureError(mets.idMets);
		std::string pathImg;
		std::stringstream sid;
		sid << mets.idMets<<"_"<< vStructureError.size();	// add a diversification per id_Mets : normally uniq 
		                                                    // multibatch ok
		                                                    // take care to not run multiple disk for different campaign from the same location 
		                                                    // perhaps adding name of campaign could be better too
		
		pathImg =  mets.date.toString("dd-MM-yyyy").toStdString() +"_nr" + sid.str() + ".png"  ;	
		db.saveStructError(mets.idMets,m_ui->txtCommentaire->toPlainText().toStdString(),
			vErrorType[m_ui->comboBoxErrorType->itemData(m_ui->comboBoxErrorType->currentIndex()).toInt()].id_type,
			pathImg,fileID,m_ui->customEdit->text().toStdString());
		
	//	QPixmap xmap = QPixmap::grabWidget(this,0,25,this->width(),this->height()-100);
		

		pathImg = BatchDetail::getBatchDetail().getErrorPath() + "/" +  pathImg;
		pixmap.save(pathImg.c_str());
		
	//	getStructureErrorPerMets();
		structView->fillListErrors();
		
		std::stringstream ss;
		ss  << m_ui->comboBoxErrorType->currentText().toStdString() << " : " << m_ui->txtCommentaire->toPlainText().toStdString();
	
		QMessageBox::information(this, tr("Error saved"),
                                 tr(" %1").arg(ss.str().c_str()));	
	
		m_ui->lbComment->setText(ss.str().c_str());	
		m_ui->txtCommentaire->clear();
		m_ui->customEdit->clear();
		m_ui->comboBoxErrorType->setCurrentIndex(0);		
	}
}

 void w_screenshoterror::setPenColor()
 { 	
	QColor newColor = QColorDialog::getColor(currentColor);
    if (newColor.isValid())  
      currentColor = newColor;
      setBoxColor();
 }
 
 void w_screenshoterror::setBoxColor()
 {
	QPalette p;	
    p.setColor(QPalette::Base,currentColor);
    m_ui->boxColor->setPalette(p); 
 }