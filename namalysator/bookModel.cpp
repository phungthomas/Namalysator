#include "bookModel.h"
#include <iostream>

bookModel::bookModel(dbrequest & _db,QObject *parent):db(_db),QAbstractTableModel(parent){
	std::cout << "DEBUG : BOOK Model" << std::endl; // 
}
bookModel::~bookModel(){
}

void bookModel::init(){
	allMets = db.getAllMets(BatchDetail::getBatchDetail().idTestSet);
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
	QString tmp = allMets[index.row()][0].value<QString>();
	return tmp.toInt(); 
}

QVariant bookModel::data(const QModelIndex &index, int role ) const{


	if ( role == Qt::CheckStateRole ) return QVariant();

	if(role==Qt::DecorationRole && index.column()==3 ){
		QVariant ret = allMets[index.row()][index.column()];
		return ret;
	}

	if ( role == Qt::DisplayRole && index.column()!=3 ) {
		QVariant ret = allMets[index.row()][index.column()];
		return ret;
	}

	return QVariant();
}

QVariant bookModel::headerData ( int section, Qt::Orientation orientation, int role ) const{
	//static char* table[]={"ID","PATH","METS", " ","Page","BIBREC_245a","BIBREC_245b","BIBREC_100a-1","BIBREC_100a-2","BIBREC_008-35-37","BIBREC_260b","BIBREC_260c","ITEMbarCode","BIBREC_SYS_NUM"};
	static char* table[]={"ID","PATH","METS", " ","BIBREC_245a","BIBREC_245b","BIBREC_100a-1","BIBREC_100a-2","BIBREC_008-35-37","BIBREC_260b","BIBREC_260c","ITEMbarCode","BIBREC_SYS_NUM"};

	QVariant ret=QVariant();
	if ( role == Qt::DisplayRole && section < 13 && section >= 0 ) {
		char * tmp = table [section];
		QString qs ( tmp );
		ret = QVariant (qs);
	}
	return ret;


}
