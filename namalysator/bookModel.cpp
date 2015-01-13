#include "bookModel.h"
#include <iostream>

bookModel::bookModel(){
	std::cout << "DEBUG : BOOK Model" << std::endl;
}
bookModel::~bookModel(){
}

QModelIndex bookModel::parent(const QModelIndex &child) const {
								 return QModelIndex();

}

int bookModel::rowCount(const QModelIndex &parent ) const{
    return 15000;
}

int bookModel::columnCount(const QModelIndex &parent ) const{
	return 5;
}


QVariant bookModel::data(const QModelIndex &index, int role ) const{
	static char* table[][5] = {{"fichier1.xml","title1","author1","REF3-1","REF4-1"},
		          {"fichier2.xml","title2","author2","REF3-2","REF4-2"},
				  {"fichier3.xml","title3","author3","REF3-3","REF4-3"},
				  {"fichier4.xml","title4","author4","REF3-4","REF4-4"},
				  {"fichier5.xml","title5","author5","REF3-5","REF4-5"},
	             };

	if ( role == Qt::CheckStateRole ) return QVariant();
	if ( role == Qt::DisplayRole ) {
		int witchRow = index.row()%5;

		char * tmp = table [witchRow][index.column()];
		QString qs ( tmp );
		QVariant ret = QVariant (qs);

		return ret;
	}
	return QVariant();
}

QVariant bookModel::headerData ( int section, Qt::Orientation orientation, int role ) const{
	static char* table[]={"File","Title","Author", "REF-1","REF-2"};
	QVariant ret=QVariant();
	if ( role == Qt::DisplayRole && section < 5 && section >= 0 ) {
		char * tmp = table [section];
		QString qs ( tmp );
		ret = QVariant (qs);
	}
	return ret;


}
