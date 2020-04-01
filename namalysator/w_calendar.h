#ifndef W_CALENDAR_H
#define W_CALENDAR_H

#include <QWidget>
#include <QDate>
#include <QCalendarWidget>
#include<QListWidgetItem>
#include <QTextCharFormat>
#include "structgui.h"
#include "dbrequest.h"
#include <map>


namespace Ui {
    class w_calendar;
}

class w_calendar : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(w_calendar)
public:
    explicit w_calendar(QWidget *parent = 0);
    virtual ~w_calendar();
    
     void setBatchDetail();
     void fillcalendar();
     void setMapComment();
       

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::w_calendar *m_ui;
    std::vector<std::pair<int,DateError>> vDateError;
    void setCalendar(int year);
    void setColor(QDate date,QColor color,QCalendarWidget *calendar);
    void displayHeader();
    void fillcalendar(int i,int year,QCalendarWidget *calendar);
    void w_calendar::createConnections();
    void displayDetails();
    void fillcomboBoxYear();
    void setRemarks();
    QCalendarWidget *getCalendarFromMonth(int month);
    std::map<QDate,DateComment> mapComment;
    std::map<int, MetsFile> listOfMetsOnDay;
    QListWidgetItem *lst;
    QDate dateComment;
    dbrequest db;
    //BatchDetail batchdetail;
    MetsFile mets;
	void clearGroupBox();
	int getLastDayOfMonth(int month,int year);
	void clearDetails();
	void fillMissingIssue();
	void setColorError(QDate date,QColor color,QCalendarWidget *calendar);

private slots:
		void clickDate(QDate);
		void clickIdMets(QListWidgetItem* item );
		void clickYear(QString);
		void validerComment();
		void addComment(QDate) ;
		void cancel();
		void viewMets();
		void showMissingIssue();
};

#endif // W_CALENDAR_H
