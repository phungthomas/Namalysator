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
	std::string tmp = allMets[index.row()][0];
	return atoi(tmp.c_str()); 
}

QVariant bookModel::data(const QModelIndex &index, int role ) const{


	if ( role == Qt::CheckStateRole ) return QVariant();
	if ( role == Qt::DisplayRole ) {
		QString qs ( allMets[index.row()][index.column()].c_str() );
		QVariant ret = QVariant (qs);

		return ret;
	}
	return QVariant();
}

QVariant bookModel::headerData ( int section, Qt::Orientation orientation, int role ) const{
	static char* table[]={"ID","PATH","METS", "UNDEF-1","UNDEF-2"};
	QVariant ret=QVariant();
	if ( role == Qt::DisplayRole && section < 5 && section >= 0 ) {
		char * tmp = table [section];
		QString qs ( tmp );
		ret = QVariant (qs);
	}
	return ret;


}
