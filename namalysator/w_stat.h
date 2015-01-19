#ifndef W_STAT_H
#define W_STAT_H

#include <QtGui/QWidget>
#include "structgui.h"
#include "dbrequest.h"
#include <map>

namespace Ui
{
    class w_stat;
}

class w_stat : public QWidget
{
    Q_OBJECT

public:
    w_stat(QWidget *parent = 0);
    ~w_stat();
	void setBatchDetail(const BatchDetail &d);
private:
    Ui::w_stat *ui;
    dbrequest db;
    //BatchDetail batchdetail;
    MetsFile mets;
    QStringList labels;
    void load();
    void drawGraph();
   
};

#endif // W_STAT_H
