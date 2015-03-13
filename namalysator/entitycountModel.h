#ifndef ENTIYCOUNTMODEL_H
#define ENTIYCOUNTMODEL_H

#include <QAbstractTableModel>
#include "dbrequest.h"

class entityCountModel : public QAbstractTableModel {
public:
	entityCountModel(dbrequest & _db,QObject *parent = 0);
	virtual ~entityCountModel();

    virtual QModelIndex parent(const QModelIndex &child) const ;
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const ;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const ;
	virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;


	virtual void init();

protected:
	dbrequest& db;
	std::map<std::string,std::map < std::string , int > > table;
	std::map<int,std::string> tableIndex;
	std::map< std::string,int> header;
	std::map<int,std::string> headerIndex;
};

#endif
