/********************************************************************************
** Form generated from reading UI file 'w_disk.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_DISK_H
#define UI_W_DISK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCalendarWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QScrollArea>
#include <QtGui/QTableWidget>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_w_disk
{
public:
    QGroupBox *groupBox_4;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *lbFileName;
    QLabel *lbIssueNumber;
    QLabel *lbIssueParsed;
    QLabel *lbPages;
    QListWidget *listSupplement;
    QCalendarWidget *calendarWidget;
    QListWidget *listMets;
    QTreeView *treeViewMets;
    QLabel *lblHeader;
    QScrollArea *scrollAreaHeader;
    QWidget *scrollAreaWidgetContents;
    QTableWidget *tableYear;

    void setupUi(QWidget *w_disk)
    {
        if (w_disk->objectName().isEmpty())
            w_disk->setObjectName(QString::fromUtf8("w_disk"));
        w_disk->resize(1014, 881);
        QFont font;
        font.setKerning(true);
        w_disk->setFont(font);
        w_disk->setMouseTracking(false);
        w_disk->setFocusPolicy(Qt::StrongFocus);
        w_disk->setAutoFillBackground(true);
        groupBox_4 = new QGroupBox(w_disk);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 250, 251, 331));
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 20, 61, 16));
        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 60, 111, 16));
        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 100, 121, 16));
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 140, 46, 14));
        label_15 = new QLabel(groupBox_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 180, 91, 16));
        lbFileName = new QLabel(groupBox_4);
        lbFileName->setObjectName(QString::fromUtf8("lbFileName"));
        lbFileName->setGeometry(QRect(10, 40, 221, 16));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        lbFileName->setFont(font1);
        lbIssueNumber = new QLabel(groupBox_4);
        lbIssueNumber->setObjectName(QString::fromUtf8("lbIssueNumber"));
        lbIssueNumber->setGeometry(QRect(10, 80, 221, 16));
        lbIssueNumber->setFont(font1);
        lbIssueParsed = new QLabel(groupBox_4);
        lbIssueParsed->setObjectName(QString::fromUtf8("lbIssueParsed"));
        lbIssueParsed->setGeometry(QRect(10, 120, 221, 16));
        lbIssueParsed->setFont(font1);
        lbPages = new QLabel(groupBox_4);
        lbPages->setObjectName(QString::fromUtf8("lbPages"));
        lbPages->setGeometry(QRect(10, 160, 221, 16));
        lbPages->setFont(font1);
        listSupplement = new QListWidget(groupBox_4);
        listSupplement->setObjectName(QString::fromUtf8("listSupplement"));
        listSupplement->setGeometry(QRect(10, 200, 231, 121));
        calendarWidget = new QCalendarWidget(w_disk);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setGeometry(QRect(10, 10, 251, 161));
        calendarWidget->setFont(font);
        calendarWidget->setMouseTracking(false);
        calendarWidget->setFocusPolicy(Qt::WheelFocus);
        calendarWidget->setAutoFillBackground(false);
        listMets = new QListWidget(w_disk);
        listMets->setObjectName(QString::fromUtf8("listMets"));
        listMets->setGeometry(QRect(10, 180, 251, 51));
        treeViewMets = new QTreeView(w_disk);
        treeViewMets->setObjectName(QString::fromUtf8("treeViewMets"));
        treeViewMets->setGeometry(QRect(270, 300, 731, 571));
        lblHeader = new QLabel(w_disk);
        lblHeader->setObjectName(QString::fromUtf8("lblHeader"));
        lblHeader->setGeometry(QRect(260, 130, 211, 21));
        scrollAreaHeader = new QScrollArea(w_disk);
        scrollAreaHeader->setObjectName(QString::fromUtf8("scrollAreaHeader"));
        scrollAreaHeader->setGeometry(QRect(270, 10, 751, 281));
        scrollAreaHeader->setBaseSize(QSize(1000, 200));
        scrollAreaHeader->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 749, 279));
        scrollAreaHeader->setWidget(scrollAreaWidgetContents);
        tableYear = new QTableWidget(w_disk);
        tableYear->setObjectName(QString::fromUtf8("tableYear"));
        tableYear->setGeometry(QRect(10, 590, 251, 281));

        retranslateUi(w_disk);

        QMetaObject::connectSlotsByName(w_disk);
    } // setupUi

    void retranslateUi(QWidget *w_disk)
    {
        w_disk->setWindowTitle(QApplication::translate("w_disk", "Form", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("w_disk", "Details of Mets", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("w_disk", "Filename :", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("w_disk", "Issue number as text:", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("w_disk", "Issue number as parsed :", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("w_disk", "Pages :", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("w_disk", "Supplements :", 0, QApplication::UnicodeUTF8));
        lbFileName->setText(QApplication::translate("w_disk", "No issue selected", 0, QApplication::UnicodeUTF8));
        lbIssueNumber->setText(QApplication::translate("w_disk", "No issue selected", 0, QApplication::UnicodeUTF8));
        lbIssueParsed->setText(QApplication::translate("w_disk", "No issue selected", 0, QApplication::UnicodeUTF8));
        lbPages->setText(QApplication::translate("w_disk", "No issue selected", 0, QApplication::UnicodeUTF8));
        lblHeader->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class w_disk: public Ui_w_disk {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_DISK_H
