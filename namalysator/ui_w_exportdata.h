/********************************************************************************
** Form generated from reading UI file 'w_exportdata.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_EXPORTDATA_H
#define UI_W_EXPORTDATA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_w_exportdata
{
public:
    QPushButton *btnExcel;
    QPushButton *pushButton_2;

    void setupUi(QWidget *w_exportdata)
    {
        if (w_exportdata->objectName().isEmpty())
            w_exportdata->setObjectName(QString::fromUtf8("w_exportdata"));
        w_exportdata->resize(600, 400);
        btnExcel = new QPushButton(w_exportdata);
        btnExcel->setObjectName(QString::fromUtf8("btnExcel"));
        btnExcel->setGeometry(QRect(70, 70, 75, 24));
        pushButton_2 = new QPushButton(w_exportdata);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(290, 40, 75, 24));

        retranslateUi(w_exportdata);

        QMetaObject::connectSlotsByName(w_exportdata);
    } // setupUi

    void retranslateUi(QWidget *w_exportdata)
    {
        w_exportdata->setWindowTitle(QApplication::translate("w_exportdata", "w_exportdata", 0, QApplication::UnicodeUTF8));
        btnExcel->setText(QApplication::translate("w_exportdata", "Export data", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("w_exportdata", "PushButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class w_exportdata: public Ui_w_exportdata {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_EXPORTDATA_H
