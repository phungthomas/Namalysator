#ifndef QWIDGETDATEERRORTAB_H_
#define QWIDGETDATEERRORTAB_H_

#include <QWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QHeaderView>
#include <QGridLayout>
#include "structgui.h"
#include "dbrequest.h"
class dateerrortab : public QWidget
{
	Q_OBJECT

	public :
		dateerrortab(int id_cat);
		int getSizeVError();
		int id_cat;
		
	private : 
		QStringList labels;
		QTableWidgetItem *newItem;
		QTableWidget *table;
		//std::vector<MetsError> vSchemaE;
		std::vector<DateError> vDateError;
		BatchDetail& batchDetail;
		void fillCombo(int id_cat,const BatchDetail &batchDetail);
		QComboBox *comboYear;
		QComboBox *comboError;
		QCheckBox *cb;
		dbrequest db;
		std::string errorGroup;
		void fillTableError(std::vector<DateError> vdateError);
	private slots :
		void accepted(bool,std::string);
		void getcbCategory(QString category);
		void getcbYear(QString year);
		//void getLine(int col,int row);
};


#endif // QWIDGETDATEERRORTAB_H_