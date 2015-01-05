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
public:
    explicit w_main(QWidget *parent = 0);
    virtual ~w_main();    
	void setBatchDetail(const BatchDetail &d);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::w_main *m_ui;
    BatchDetail batch;   
    QAction *openAct;
	QAction *modeBookAct;
	QAction *openErrorAction;
	QAction *openBookBrowserAction;
	QAction *openDiskAnalyze;
	QAction *openCalendarAction;	
	QAction *openStructureAction;
	QAction *openTitleCheck;	
	QAction *openSelectBatch;
	QAction *openInventaire;
	QToolBar *fileTools;	

private slots:
		void createActions();
		void newsPaperActions();
		void booksActions();
		void openSummaryErrorsWindow();
		void openCalendarWindow();
		void parseBatch();
		void modeBook();
		void modeNewsPaper();
		void openStructureWindow();
		void openTitleCheckWindow();		
		void openSelectBatchWindow();    
		void openInventaireWindow();
		void openBookBrowser();
};

#endif // W_MAIN_H
