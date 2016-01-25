// —— File itemdelegate.h ——
#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H
 
#include <QStyledItemDelegate>
#include "dbrequest.h"
#include <QComboBox>
#include <vector>
 
class ComboBoxItemDelegate : public QStyledItemDelegate
{
 Q_OBJECT
 
public:
 ComboBoxItemDelegate(dbrequest & _db,QObject *parent = 0);
 ~ComboBoxItemDelegate();
 
virtual QWidget *createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
 virtual void setEditorData ( QWidget *editor, const QModelIndex &index ) const;
 virtual void setModelData ( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const;

 private:
	 std::vector<int> tabl;
 protected:
	dbrequest& db;


 
};
 
#endif // ITEMDELEGATE_H