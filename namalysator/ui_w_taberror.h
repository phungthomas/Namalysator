/********************************************************************************
** Form generated from reading UI file 'w_taberror.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_TABERROR_H
#define UI_W_TABERROR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_w_taberror
{
public:
    QTableWidget *tableWidget;
    QComboBox *comboBox;

    void setupUi(QWidget *w_taberror)
    {
        if (w_taberror->objectName().isEmpty())
            w_taberror->setObjectName(QString::fromUtf8("w_taberror"));
        w_taberror->resize(623, 558);
        tableWidget = new QTableWidget(w_taberror);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(20, 40, 591, 301));
        comboBox = new QComboBox(w_taberror);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(190, 200, 101, 31));

        retranslateUi(w_taberror);

        QMetaObject::connectSlotsByName(w_taberror);
    } // setupUi

    void retranslateUi(QWidget *w_taberror)
    {
        w_taberror->setWindowTitle(QCoreApplication::translate("w_taberror", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("w_taberror", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("w_taberror", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("w_taberror", "hg", nullptr));
    } // retranslateUi

};

namespace Ui {
    class w_taberror: public Ui_w_taberror {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_TABERROR_H
