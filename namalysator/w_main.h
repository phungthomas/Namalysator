#ifndef W_MAIN_H
#define W_MAIN_H

#include <QtGui/QMainWindow>
#include "structgui.h"

#include <QToolBar>
#include <QHeaderView>
#include <QTableView>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QSplitter>
#include "w_disk.h"

namespace Ui {
    class w_main;
}

class w_main : public QMainWindow {
    Q_OBJECT
    Q_DISABLE_COPY(w_main)
private:
	static std::string title;
public:
    explicit w_main(QWidget *parent = 0);
    virtual ~w_main();    
	void setBatchDetail();


	void titleChange(std::string sub,std::string _title = title);

protected:
    virtual void changeEvent(QEvent *e);

private:
	
	std::string subTitle;
    Ui::w_main *m_ui;
    QAction *openAct;
	QAction *openErrorAction;
	QAction *openBookBrowserAction;
	QAction *openDiskAnalyze;
	QAction *openCalendarAction;	
	QAction *openStructureAction;
	//QAction *openTitleCheck;	
	QAction *openSelectBatch;
	QToolBar *fileTools;	



public slots:
		void createActions();
		void newsPaperActions();
		void openSummaryErrorsWindow();
		void openCalendarWindow();
		void parseBatch();
		void modeNewsPaper();
		void openStructureWindow();
		//void openTitleCheckWindow();		
		void openSelectBatchWindow();    
		void openReport();
		void openStart(std::string);
		void exit();
		void exportData();
};

#endif // W_MAIN_H
