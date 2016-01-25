// —— File itemdelegate.cpp ——
#include "itemdelegate.h"

#include <map>
#include <string>
#include <sstream>
#include <QErrorMessage>
 
ComboBoxItemDelegate::ComboBoxItemDelegate(dbrequest & _db,QObject *parent)
:db(_db), QStyledItemDelegate(parent)
{
}
 
 
ComboBoxItemDelegate::~ComboBoxItemDelegate()
{
}
 
 
QWidget* ComboBoxItemDelegate::createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
 // ComboBox ony in column 2
 if(index.column() != 0)return QStyledItemDelegate::createEditor(parent, option, index);
 
// Create the combobox and populate it
 QComboBox* cb = new QComboBox(parent);
 //QObject::connect(cb,SIGNAL(currentIndexChanged(int)),this,SLOT(setData(int)));

 std::map<std::string,int> label = db.loadLabel();

 cb->addItem(QString(""),QVariant::fromValue(-1));


 for ( std::map<std::string,int>::iterator it = label.begin(); it != label.end(); ++it ){
	 QVariant id (it->second);
	 cb->addItem(QString((it->first).c_str()),id);
 }
 return cb;
}
 
void ComboBoxItemDelegate::setEditorData ( QWidget *editor, const QModelIndex &index ) const
{
 if(QComboBox* cb = qobject_cast<QComboBox*>(editor)) {
 // get the index of the text in the combobox that matches the current value of the itenm
 QString currentText = index.data(Qt::EditRole).toString();
 int cbIndex = cb->findText(currentText);
 // if it is valid, adjust the combobox
 if(cbIndex >= 0)
 cb->setCurrentIndex(cbIndex);
 } else {
 QStyledItemDelegate::setEditorData(editor, index);
 }
}
 
void ComboBoxItemDelegate::setModelData ( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const
{
 if(QComboBox*cb = qobject_cast<QComboBox*>(editor))
 // save the current text of the combo box as the current value of the item
 model ->setData(index,cb->itemData(cb->currentIndex()));
 else
 QStyledItemDelegate::setModelData(editor, model, index);
}
