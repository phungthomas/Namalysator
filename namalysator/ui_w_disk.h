/********************************************************************************
** Form generated from reading UI file 'w_disk.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_DISK_H
#define UI_W_DISK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_w_disk
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QCalendarWidget *calendarWidget;
    QListWidget *listMets;
    QGroupBox *groupBox_4;
    QFormLayout *formLayout;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *lbPages;
    QLabel *lbIssueParsed;
    QLabel *lbIssueNumber;
    QLabel *lbFileName;
    QListWidget *listSupplement;
    QTableWidget *tableYear;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollAreaHeader;
    QWidget *scrollAreaWidgetContents;
    QTreeView *treeViewMets;
    QLabel *lblHeader;

    void setupUi(QWidget *w_disk)
    {
        if (w_disk->objectName().isEmpty())
            w_disk->setObjectName(QString::fromUtf8("w_disk"));
        w_disk->resize(871, 720);
        QFont font;
        font.setKerning(true);
        w_disk->setFont(font);
        w_disk->setMouseTracking(false);
        w_disk->setFocusPolicy(Qt::StrongFocus);
        w_disk->setAutoFillBackground(true);
        horizontalLayout = new QHBoxLayout(w_disk);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(w_disk);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(0, 0));
        widget->setMaximumSize(QSize(300, 16777215));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        calendarWidget = new QCalendarWidget(widget);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        sizePolicy.setHeightForWidth(calendarWidget->sizePolicy().hasHeightForWidth());
        calendarWidget->setSizePolicy(sizePolicy);
        calendarWidget->setMinimumSize(QSize(200, 200));
        calendarWidget->setMaximumSize(QSize(16000, 16000));
        calendarWidget->setFont(font);
        calendarWidget->setMouseTracking(false);
        calendarWidget->setFocusPolicy(Qt::WheelFocus);
        calendarWidget->setAutoFillBackground(false);

        verticalLayout_2->addWidget(calendarWidget);

        listMets = new QListWidget(widget);
        listMets->setObjectName(QString::fromUtf8("listMets"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listMets->sizePolicy().hasHeightForWidth());
        listMets->setSizePolicy(sizePolicy1);
        listMets->setMinimumSize(QSize(50, 100));
        listMets->setMaximumSize(QSize(16000, 16000));

        verticalLayout_2->addWidget(listMets);

        groupBox_4 = new QGroupBox(widget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(0, 180));
        groupBox_4->setMaximumSize(QSize(300, 200));
        formLayout = new QFormLayout(groupBox_4);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_11);

        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_12);

        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_13);

        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_14);

        label_15 = new QLabel(groupBox_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_15);

        lbPages = new QLabel(groupBox_4);
        lbPages->setObjectName(QString::fromUtf8("lbPages"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        lbPages->setFont(font1);

        formLayout->setWidget(6, QFormLayout::FieldRole, lbPages);

        lbIssueParsed = new QLabel(groupBox_4);
        lbIssueParsed->setObjectName(QString::fromUtf8("lbIssueParsed"));
        lbIssueParsed->setFont(font1);

        formLayout->setWidget(4, QFormLayout::FieldRole, lbIssueParsed);

        lbIssueNumber = new QLabel(groupBox_4);
        lbIssueNumber->setObjectName(QString::fromUtf8("lbIssueNumber"));
        lbIssueNumber->setFont(font1);

        formLayout->setWidget(2, QFormLayout::FieldRole, lbIssueNumber);

        lbFileName = new QLabel(groupBox_4);
        lbFileName->setObjectName(QString::fromUtf8("lbFileName"));
        lbFileName->setFont(font1);

        formLayout->setWidget(0, QFormLayout::FieldRole, lbFileName);

        listSupplement = new QListWidget(groupBox_4);
        listSupplement->setObjectName(QString::fromUtf8("listSupplement"));

        formLayout->setWidget(8, QFormLayout::FieldRole, listSupplement);


        verticalLayout_2->addWidget(groupBox_4);

        tableYear = new QTableWidget(widget);
        tableYear->setObjectName(QString::fromUtf8("tableYear"));
        tableYear->setMinimumSize(QSize(0, 0));

        verticalLayout_2->addWidget(tableYear);


        horizontalLayout->addWidget(widget);

        widget_2 = new QWidget(w_disk);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy2);
        widget_2->setMinimumSize(QSize(0, 0));
        verticalLayout_3 = new QVBoxLayout(widget_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        scrollAreaHeader = new QScrollArea(widget_2);
        scrollAreaHeader->setObjectName(QString::fromUtf8("scrollAreaHeader"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(scrollAreaHeader->sizePolicy().hasHeightForWidth());
        scrollAreaHeader->setSizePolicy(sizePolicy3);
        scrollAreaHeader->setMinimumSize(QSize(0, 200));
        scrollAreaHeader->setMaximumSize(QSize(16000, 16000));
        scrollAreaHeader->setBaseSize(QSize(1000, 200));
        scrollAreaHeader->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 516, 198));
        scrollAreaHeader->setWidget(scrollAreaWidgetContents);

        verticalLayout_3->addWidget(scrollAreaHeader);

        treeViewMets = new QTreeView(widget_2);
        treeViewMets->setObjectName(QString::fromUtf8("treeViewMets"));
        sizePolicy2.setHeightForWidth(treeViewMets->sizePolicy().hasHeightForWidth());
        treeViewMets->setSizePolicy(sizePolicy2);

        verticalLayout_3->addWidget(treeViewMets);


        horizontalLayout->addWidget(widget_2);

        lblHeader = new QLabel(w_disk);
        lblHeader->setObjectName(QString::fromUtf8("lblHeader"));

        horizontalLayout->addWidget(lblHeader);


        retranslateUi(w_disk);

        QMetaObject::connectSlotsByName(w_disk);
    } // setupUi

    void retranslateUi(QWidget *w_disk)
    {
        w_disk->setWindowTitle(QCoreApplication::translate("w_disk", "Form", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("w_disk", "Details of Mets", nullptr));
        label_11->setText(QCoreApplication::translate("w_disk", "Filename :", nullptr));
        label_12->setText(QCoreApplication::translate("w_disk", "Issue number as text:", nullptr));
        label_13->setText(QCoreApplication::translate("w_disk", "Issue number as parsed :", nullptr));
        label_14->setText(QCoreApplication::translate("w_disk", "Pages :", nullptr));
        label_15->setText(QCoreApplication::translate("w_disk", "Supplements :", nullptr));
        lbPages->setText(QCoreApplication::translate("w_disk", "No issue selected", nullptr));
        lbIssueParsed->setText(QCoreApplication::translate("w_disk", "No issue selected", nullptr));
        lbIssueNumber->setText(QCoreApplication::translate("w_disk", "No issue selected", nullptr));
        lbFileName->setText(QCoreApplication::translate("w_disk", "No issue selected", nullptr));
        lblHeader->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class w_disk: public Ui_w_disk {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_DISK_H
