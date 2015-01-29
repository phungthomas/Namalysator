#include <parammodel.h>
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
	static char* tableTitle[]={"key","value","U", "U"};
	QVariant ret=QVariant();

	if ( role == Qt::DisplayRole && section < 3 && section >= 0 ) {
		char * tmp = tableTitle [section];
		QString qs ( tmp );
		ret = QVariant (qs);
	}

	return ret;
}

void paramModel::init(std::map<std::string,std::string> map){
	std::vector<QVariant> vect;

	table.clear();
	
	for ( std::map<std::string,std::string>::iterator it=map.begin(); it != map.end(); it++ ){
		vect.clear();
		vect.push_back(QString(it->first.c_str()));
		vect.push_back(QString(it->second.c_str()));
		table.push_back(vect);
	};
	
}