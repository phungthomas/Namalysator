#include <QtGui/QApplication>
#include "w_selectbatch.h"

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	w_selectBatch *gui = new w_selectBatch();
	gui->show();	
	return a.exec();
}

