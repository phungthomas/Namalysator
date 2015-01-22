#ifndef W_SCREENSHOTERROR_H
#define W_SCREENSHOTERROR_H

#include <QtGui/QWidget>
#include "structgui.h"
#include <QMouseEvent>
#include <QMoveEvent>
#include "dbrequest.h"
#include <QPainter>
#include "w_structview.h"
namespace Ui {
    class w_screenshoterror;
}
//! screenshoterror class
class w_screenshoterror : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(w_screenshoterror)
public:
    explicit w_screenshoterror(QWidget *parent = 0);
    virtual ~w_screenshoterror();
    
    //! set batchdetail + current image to show errors. 
	void setBatchDetailImage(QPixmap pix,MetsFile mets,w_structview *w,std::string);	
protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::w_screenshoterror *m_ui;
    w_structview *structView;
    //BatchDetail batchDetail;
    MetsFile mets;
    dbrequest db;
    QPixmap pixmap,originalPixmap;
    void fillComboBoxErrortype();
    void loadImage();
    std::vector<ErrorType> vErrorType;      
    void mousePressEvent(QMouseEvent *event);      
    void mouseReleaseEvent(QMouseEvent *event);   
    int clickCount;    
    int point1X,point1Y,point2X,point2Y ;
	QColor currentColor;
	int x,y,width,height;
	void createConnections();
	void init();
	void setBoxColor();	
	std::string fileID;
	
private slots: 
	void saveError();
	void clearPainter();
	void setPenColor();
	void close();
	
};

#endif // W_SCREENSHOTERROR_H
