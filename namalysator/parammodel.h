#ifndef _PARAMMODEL_H
#define _PARAMMODEL_H


#include <QAbstractTableModel>
#include <map>
#include <string>
#include <vector>
#include <QVariant>

class paramModel: public QAbstractTableModel{

public:
	paramModel();
	virtual ~paramModel();

	virtual QModelIndex parent(const QModelIndex &child) const ;
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const ;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const ;
	virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	void init(std::map<std::string,std::string>);

private:
	std::vector<std::vector<QVariant> > table;
};

#endif