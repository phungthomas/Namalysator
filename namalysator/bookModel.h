#ifndef _BOOKMODEL_H
#define _BOOKMODEL_H

#include <QAbstractTableModel>
//** implement model of book to be able to developp : use by the tableview widget

class bookModel : public QAbstractTableModel {
public:
	bookModel();
	virtual ~bookModel();

    virtual QModelIndex parent(const QModelIndex &child) const ;
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const ;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const ;
	virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

private:

};


#endif