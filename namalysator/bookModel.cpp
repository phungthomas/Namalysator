#include "bookModel.h"
#include <iostream>
#include <QErrorMessage>
#include <sstream>

bookModel::bookModel(dbrequest & _db,QObject *parent):db(_db),QAbstractTableModel(parent){
}
bookModel::~bookModel(){
}

void bookModel::init(bool sampling){
	allMets = db.getAllMets(BatchDetail::getBatchDetail().idTestSet,sampling);
	emit endResetModel();
}

void bookModelInventory::init(){
	allMets = db.getAllBooks(BatchDetail::getBatchDetail().idTestSet);
}

QModelIndex bookModel::parent(const QModelIndex &child) const {
								 return QModelIndex();
		
}

int bookModel::rowCount(const QModelIndex &parent ) const{
	return allMets.size();
}

int bookModel::columnCount(const QModelIndex &parent ) const{
	return allMets.size()!=0 ? allMets[0].size() : 0;
}

int bookModel::idMets ( const QModelIndex &index ){
	QString tmp = allMets[index.row()][1].value<QString>();
	return tmp.toInt(); 
}

QVariant bookModel::data(const QModelIndex &index, int role ) const{


	if ( role == Qt::CheckStateRole ) return QVariant();

	if(role==Qt::DecorationRole && index.column()==4 ){
		QVariant ret = allMets[index.row()][index.column()];
		return ret;
	}

	if ( role == Qt::DisplayRole && index.column()!=4 ) {
		QVariant ret = allMets[index.row()][index.column()];
		return ret;
	}

	return QVariant();
}

QVariant bookModelInventory::data(const QModelIndex &index, int role ) const{

	if ( role == Qt::CheckStateRole ) return QVariant();

		if ( role == Qt::DisplayRole ) {
		QVariant ret = allMets[index.row()][index.column()];
		return ret;
	}

	return QVariant();
}

QVariant bookModel::headerData ( int section, Qt::Orientation orientation, int role ) const{
	//static char* table[]={"ID","PATH","METS", " ","Page","BIBREC_245a","BIBREC_245b","BIBREC_100a-1","BIBREC_100a-2","BIBREC_008-35-37","BIBREC_260b","BIBREC_260c","ITEMbarCode","BIBREC_SYS_NUM"};
	static char* table[]={"PROGRESS","ID","PATH","METS", " ","BIBREC_245a",
		                  "BIBREC_100a","BIBREC_260b","ITEMbarCode","BIBREC_SYS_NUM","CHECKED","R","N","D"};

	QVariant ret=QVariant();
	if ( role == Qt::DisplayRole && section < 12 && section >= 0 ) {
		char * tmp = table [section];
		QString qs ( tmp );
		ret = QVariant (qs);
	}
	return ret;
}


QVariant bookModelInventory::headerData ( int section, Qt::Orientation orientation, int role  ) const{
	static char* table[]={"CHECKED","BATCH","language", "BIBREC_SYS_NUM","ITEMbarCode","BIBREC_245a",
		                  "BIBREC_100a","BIBREC_260b","BIBREC_008_7_10","N","D"};

	QVariant ret=QVariant();
	if ( role == Qt::DisplayRole && section < 9 && section >= 0 ) {
		char * tmp = table [section];
		QString qs ( tmp );
		ret = QVariant (qs);
	}
	return ret;
}

bookModelE::bookModelE(dbrequest & _db,QObject *parent):bookModel(_db,parent){
}

bookModelE::~bookModelE(){
}

Qt::ItemFlags bookModelE::flags(const QModelIndex &index) const {

	Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);
	if ( index.isValid() ) {
		if (index.column()==0)
		return Qt::ItemIsEditable | defaultFlags;
	}
	return defaultFlags;

}

bool bookModelE::setData(const QModelIndex &index, const QVariant &value, int /* role */)
{

	std::stringstream ss;
	int valueI = value.value<int>();
	ss << "DEBUG :" << valueI << std::endl << " COL " << index.column() << " ROW " << index.row() << std::endl ;
	static QErrorMessage* Qerror= new QErrorMessage();
	Qerror->showMessage(ss.str().c_str());

	(this->allMets)[index.row()][0]=value;

    if (index.column() != 0)
        return false;

    
    return true;
}