/********************************************************************************
** Form generated from reading UI file 'w_titlecheck.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_TITLECHECK_H
#define UI_W_TITLECHECK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_w_titlecheck
{
public:
    QTableWidget *tableWidget;
    QPushButton *btnLoad;
    QPushButton *btnSave;
    QPushButton *btnReduceSize;
    QPushButton *btnOrginalSize;
    QProgressBar *progressBar;
    QLabel *lbWait;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *lbTotal;
    QLabel *label2;
    QLabel *lbError;
    QLabel *label_2;
    QLabel *lbPercentage;
    QPushButton *btnExport;

    void setupUi(QWidget *w_titlecheck)
    {
        if (w_titlecheck->objectName().isEmpty())
            w_titlecheck->setObjectName(QString::fromUtf8("w_titlecheck"));
        w_titlecheck->resize(1062, 798);
        tableWidget = new QTableWidget(w_titlecheck);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(0, 20, 1011, 681));
        tableWidget->setColumnCount(4);
        btnLoad = new QPushButton(w_titlecheck);
        btnLoad->setObjectName(QString::fromUtf8("btnLoad"));
        btnLoad->setGeometry(QRect(30, 710, 75, 24));
        btnSave = new QPushButton(w_titlecheck);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setGeometry(QRect(130, 710, 75, 24));
        btnReduceSize = new QPushButton(w_titlecheck);
        btnReduceSize->setObjectName(QString::fromUtf8("btnReduceSize"));
        btnReduceSize->setGeometry(QRect(610, 710, 75, 24));
        btnOrginalSize = new QPushButton(w_titlecheck);
        btnOrginalSize->setObjectName(QString::fromUtf8("btnOrginalSize"));
        btnOrginalSize->setGeometry(QRect(720, 710, 75, 24));
        progressBar = new QProgressBar(w_titlecheck);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(270, 760, 211, 23));
        progressBar->setValue(24);
        lbWait = new QLabel(w_titlecheck);
        lbWait->setObjectName(QString::fromUtf8("lbWait"));
        lbWait->setGeometry(QRect(340, 740, 71, 16));
        layoutWidget = new QWidget(w_titlecheck);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(260, 720, 281, 16));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lbTotal = new QLabel(layoutWidget);
        lbTotal->setObjectName(QString::fromUtf8("lbTotal"));

        horizontalLayout->addWidget(lbTotal);

        label2 = new QLabel(layoutWidget);
        label2->setObjectName(QString::fromUtf8("label2"));

        horizontalLayout->addWidget(label2);

        lbError = new QLabel(layoutWidget);
        lbError->setObjectName(QString::fromUtf8("lbError"));

        horizontalLayout->addWidget(lbError);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        lbPercentage = new QLabel(layoutWidget);
        lbPercentage->setObjectName(QString::fromUtf8("lbPercentage"));

        horizontalLayout->addWidget(lbPercentage);

        btnExport = new QPushButton(w_titlecheck);
        btnExport->setObjectName(QString::fromUtf8("btnExport"));
        btnExport->setGeometry(QRect(904, 710, 91, 24));

        retranslateUi(w_titlecheck);

        QMetaObject::connectSlotsByName(w_titlecheck);
    } // setupUi

    void retranslateUi(QWidget *w_titlecheck)
    {
        w_titlecheck->setWindowTitle(QApplication::translate("w_titlecheck", "Form", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("w_titlecheck", "Title", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("w_titlecheck", "Character", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("w_titlecheck", "Error", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("w_titlecheck", "Image", 0, QApplication::UnicodeUTF8));
        btnLoad->setText(QApplication::translate("w_titlecheck", "Load", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("w_titlecheck", "Save", 0, QApplication::UnicodeUTF8));
        btnReduceSize->setText(QApplication::translate("w_titlecheck", "Reduce size", 0, QApplication::UnicodeUTF8));
        btnOrginalSize->setText(QApplication::translate("w_titlecheck", "Original Size", 0, QApplication::UnicodeUTF8));
        lbWait->setText(QApplication::translate("w_titlecheck", "Please wait", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("w_titlecheck", "Total :", 0, QApplication::UnicodeUTF8));
        lbTotal->setText(QString());
        label2->setText(QApplication::translate("w_titlecheck", "Error : ", 0, QApplication::UnicodeUTF8));
        lbError->setText(QString());
        label_2->setText(QApplication::translate("w_titlecheck", "Percentage :", 0, QApplication::UnicodeUTF8));
        lbPercentage->setText(QString());
        btnExport->setText(QApplication::translate("w_titlecheck", "Export to excel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class w_titlecheck: public Ui_w_titlecheck {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_TITLECHECK_H
