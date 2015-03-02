#include "parammodel.h"
#include <QString>


paramModel::paramModel(){

}
paramModel::~paramModel(){
}

QModelIndex paramModel::parent(const QModelIndex &) const {
	return QModelIndex();
}
int paramModel::rowCount(const QModelIndex &) const {
	return table.size();
}

int paramModel::columnCount(const QModelIndex &) const {
	return table.size()!=0 ? table[0].size() : 0;
}

QVariant paramModel::data(const QModelIndex &index, int role) const {
	if ( role == Qt::DisplayRole ) {
		QVariant ret = table[index.row()][index.column()];
		return ret;
	}
	return QVariant();
}

QVariant paramModel::headerData ( int section, Qt::Orientation orientation, int role  ) const{
	static char* tableTitle[]={"key","value","key","value","U","U"};
	QVariant ret=QVariant();

	if ( role == Qt::DisplayRole && section < 5 && section >= 0 ) {
		char * tmp = tableTitle [section];
		QString qs ( tmp );
		ret = QVariant (qs);
	}

	return ret;
}

void paramModel::init(std::map<std::string,std::string> map){
	std::vector<QVariant> vect;
	static QString ok("Yes");
	static QString nok("No");


	table.clear();
	vect.clear();
	
	for ( std::map<std::string,std::string>::iterator it=map.begin(); it != map.end(); it++ ){
		
		vect.push_back(QString(it->first.c_str()));
		int rr = atoi (it->second.c_str());
		switch(rr){
			case 1: vect.push_back(ok); break;
			case 0: vect.push_back(nok); break;
			default: vect.push_back(QString(it->second.c_str())); break;
		}
		

			table.push_back(vect);
			vect.clear();
		
	};
	
}