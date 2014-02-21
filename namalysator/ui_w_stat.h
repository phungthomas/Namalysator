/********************************************************************************
** Form generated from reading UI file 'w_stat.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_STAT_H
#define UI_W_STAT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_w_stat
{
public:
    QTableWidget *table;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;

    void setupUi(QWidget *w_stat)
    {
        if (w_stat->objectName().isEmpty())
            w_stat->setObjectName(QString::fromUtf8("w_stat"));
        w_stat->resize(1105, 867);
        table = new QTableWidget(w_stat);
        table->setObjectName(QString::fromUtf8("table"));
        table->setGeometry(QRect(10, 40, 661, 311));
        gridLayoutWidget = new QWidget(w_stat);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 360, 641, 391));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(w_stat);

        QMetaObject::connectSlotsByName(w_stat);
    } // setupUi

    void retranslateUi(QWidget *w_stat)
    {
        w_stat->setWindowTitle(QApplication::translate("w_stat", "w_stat", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class w_stat: public Ui_w_stat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_STAT_H
