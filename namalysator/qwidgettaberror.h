#ifndef QWIDGETTABERRORS_H_
#define QWIDGETTABERRORS_H_

#include <QtGui/QWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QHeaderView>
#include <QGridLayout>
#include "structgui.h"
#include "dbrequest.h"
#include <QPlainTextEdit>
#include <QScrollArea>
#include "codeeditor.h"
#include <QSplitter>
#include <QPushButton>
class tabErrors : public QWidget
{
	Q_OBJECT

	public :
		tabErrors(int id_cat,BatchDetail &batch);
		int getSizeVError();
		int id_cat;
		//QPlainTextEdit *plainTextEdit;
	private : 
		QStringList labels;
		QTableWidgetItem *newItem;
		QTableWidget *table;
		std::vector<MetsError> vSchemaE;
		BatchDetail& batch;
		void fillCombo(int id_cat,const BatchDetail &batchDetail);
		QComboBox *comboYear;
		QComboBox *comboError;		
		dbrequest db;		
		void fillTableError(std::vector<MetsError> vSchemaE);
		QPlainTextEdit *editor;
		void findLine(const BatchDetail &batchDetail,MetsError s);
		void createConnections();
		QPushButton *btnNext;	
		std::string search_item;
		
	private slots :
		void accepted(bool,std::string);
		void getcbCategory(QString category);
		void getcbYear(QString year);
		void lineChanged(int col,int row);
		void findNext();		
};

#endif // QWIDGETTABERRORS_H_