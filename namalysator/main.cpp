#include <QApplication>
#include "w_selectbatch.h"
#include "w_main.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	//w_selectBatch *gui = new w_selectBatch();
	//gui->show();
	w_main * ww = new w_main();
	//ww->setBatchDetail();
	ww->createActions();
	ww->openSelectBatchWindow();
	ww->show();
	return a.exec();
}

