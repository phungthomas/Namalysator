#include "entitycountModel.h"

entityCountModel::entityCountModel(dbrequest & _db,QObject *parent): QAbstractTableModel(parent), db(_db){
}

entityCountModel::~entityCountModel(){

}

void entityCountModel::init(){

	db.loadEntityCount(table,header);

	int pos=0;
	for ( std::map< string,int>::iterator it = header.begin();it != header.end(); it++){
		headerIndex[ pos++ ]= it->first;
	}

	pos = 0;
	for ( std::map<std::string,std::map < string , int > >::iterator it = table.begin();it != table.end(); it++){
		tableIndex[ pos++ ]= it->first;
	};

}

QModelIndex entityCountModel::parent(const QModelIndex &child) const {
	return  QModelIndex();
}

int entityCountModel::rowCount(const QModelIndex &parent) const {
	return table.size();
}

int entityCountModel::columnCount(const QModelIndex &parent) const {
	return headerIndex.size()+1;
}

QVariant entityCountModel::data(const QModelIndex &index, int role) const {
	
	QVariant ret;

	int columnIdx = index.column();

	if (role == Qt::TextAlignmentRole) {
		if ( columnIdx > 0 )
		return Qt::AlignRight;
	};

	if ( role == Qt::DisplayRole ) {

		if ( columnIdx == 0 ) {
			std::map<int,std::string>::const_iterator itt = tableIndex.find( index.row() );
			if ( itt == tableIndex.end()) return QVariant(); // non existing row

			std::string idx = itt->second;
			return QVariant(QString(idx.c_str()));
		}else{
			columnIdx --;
		}
		
		std::map<int,std::string>::const_iterator it = headerIndex.find( columnIdx );
		if ( it == headerIndex.end()) return QVariant(); // non existing column
		
		std::string column = it->second ;

		std::map<int,std::string>::const_iterator itt = tableIndex.find( index.row() );
		if ( itt == tableIndex.end()) return QVariant(); // non existing row

		std::string idx = itt->second;
		std::map<std::string,std::map < std::string , int > >::const_iterator ittt = table.find(idx);
		if ( ittt == table.end() ) return QVariant(); 

		std::map < std::string , int >::const_iterator itttt = ittt->second .find ( column );

		if ( itttt == ittt->second.end() ) return QVariant(); 

		int count = itttt ->second;

		ret = QVariant(count);
		
	};

	return ret;
}

QVariant entityCountModel::headerData ( int section, Qt::Orientation orientation, int role) const{

	QVariant ret;
	if ( role == Qt::DisplayRole ){
		
		if ( section == 0 ) return QVariant ( QString ( "FILENAME" ) );

		std::map<int,string>::const_iterator it = headerIndex.find(section-1);
		if ( it == headerIndex.end()) return QVariant();
		ret = QVariant ( QString ( it->second.c_str() ) );
		
	};

	return ret;

}