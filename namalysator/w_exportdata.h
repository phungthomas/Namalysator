#ifndef W_EXPORTDATA_H
#define W_EXPORTDATA_H

#include <QtWidgets>
#include "dbrequest.h"

namespace Ui
{
    class w_exportdata;
}

class w_exportdata : public QWidget
{
    Q_OBJECT

public:
    w_exportdata(QWidget *parent = 0);
    ~w_exportdata();
    void setBatchDetail(const BatchDetail &d);

private:
    Ui::w_exportdata *ui;
       dbrequest db;
    BatchDetail batchdetail;
private slots : 
	void exportexcel();    

};

#endif // W_EXPORTDATA_H
