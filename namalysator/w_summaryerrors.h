#ifndef W_SUMMARYERRORS_H
#define W_SUMMARYERRORS_H

#include <QtGui/QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include "structgui.h"
#include "dbrequest.h"
namespace Ui {
    class w_summaryerrors;
}

class w_summaryerrors : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(w_summaryerrors)
public:
    explicit w_summaryerrors(QWidget *parent = 0);
    virtual ~w_summaryerrors();
	 void setBatchDetail(const BatchDetail &d);
protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::w_summaryerrors *m_ui;
    QStringList labels;
    QTableWidgetItem *newItem;
    BatchDetail batch;    
    void loadTableSummary();
    void loadTextbox();
    dbrequest db;
};

#endif // W_SUMMARYERRORS_H
