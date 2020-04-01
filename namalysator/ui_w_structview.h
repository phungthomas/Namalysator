/********************************************************************************
** Form generated from reading UI file 'w_structview.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_STRUCTVIEW_H
#define UI_W_STRUCTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_w_structview
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QCalendarWidget *calendarWidget;
    QListWidget *listSampling;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnUndo;
    QPushButton *btnChecked;
    QListWidget *listMets;
    QTreeWidget *treeWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnZoomIn;
    QPushButton *zoomNormal;
    QPushButton *btnZoomOut;
    QPushButton *btnPrevious;
    QSpinBox *lblPage;
    QLabel *label_2;
    QLabel *lblPageEnd;
    QPushButton *btnNext;
    QPushButton *btnClearPainter;
    QPushButton *btnFull;
    QHBoxLayout *horizontalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_4;
    QListWidget *listErrors;
    QVBoxLayout *verticalLayout_6;
    QPushButton *btnDeleteSelectedItem;
    QPushButton *btnViewHtml;
    QVBoxLayout *verticalLayout_4;
    QLabel *lbl_blocking;
    QLabel *lbl_major;
    QLabel *lbl_minor;
    QVBoxLayout *verticalLayout_5;
    QPushButton *btnError;
    QPushButton *btnStructure;
    QPushButton *btnViewMets;
    QPushButton *btnViewDir;

    void setupUi(QWidget *w_structview)
    {
        if (w_structview->objectName().isEmpty())
            w_structview->setObjectName(QString::fromUtf8("w_structview"));
        w_structview->resize(1194, 900);
        verticalLayout_2 = new QVBoxLayout(w_structview);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(w_structview);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));

        verticalLayout_3->addLayout(horizontalLayout_6);

        calendarWidget = new QCalendarWidget(w_structview);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(calendarWidget->sizePolicy().hasHeightForWidth());
        calendarWidget->setSizePolicy(sizePolicy1);
        calendarWidget->setMinimumSize(QSize(0, 180));
        calendarWidget->setMaximumSize(QSize(300, 180));

        verticalLayout_3->addWidget(calendarWidget);

        listSampling = new QListWidget(w_structview);
        listSampling->setObjectName(QString::fromUtf8("listSampling"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(listSampling->sizePolicy().hasHeightForWidth());
        listSampling->setSizePolicy(sizePolicy2);
        listSampling->setMinimumSize(QSize(0, 180));
        listSampling->setMaximumSize(QSize(300, 180));

        verticalLayout_3->addWidget(listSampling);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        btnUndo = new QPushButton(w_structview);
        btnUndo->setObjectName(QString::fromUtf8("btnUndo"));
        btnUndo->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_5->addWidget(btnUndo);

        btnChecked = new QPushButton(w_structview);
        btnChecked->setObjectName(QString::fromUtf8("btnChecked"));
        btnChecked->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_5->addWidget(btnChecked);


        verticalLayout_3->addLayout(horizontalLayout_5);

        listMets = new QListWidget(w_structview);
        listMets->setObjectName(QString::fromUtf8("listMets"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(listMets->sizePolicy().hasHeightForWidth());
        listMets->setSizePolicy(sizePolicy3);
        listMets->setMinimumSize(QSize(0, 60));
        listMets->setMaximumSize(QSize(300, 60));

        verticalLayout_3->addWidget(listMets);

        treeWidget = new QTreeWidget(w_structview);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("Table of contents"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy4);
        treeWidget->setMaximumSize(QSize(300, 16777215));
        treeWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        treeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        verticalLayout_3->addWidget(treeWidget);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnZoomIn = new QPushButton(w_structview);
        btnZoomIn->setObjectName(QString::fromUtf8("btnZoomIn"));

        horizontalLayout_3->addWidget(btnZoomIn);

        zoomNormal = new QPushButton(w_structview);
        zoomNormal->setObjectName(QString::fromUtf8("zoomNormal"));

        horizontalLayout_3->addWidget(zoomNormal);

        btnZoomOut = new QPushButton(w_structview);
        btnZoomOut->setObjectName(QString::fromUtf8("btnZoomOut"));

        horizontalLayout_3->addWidget(btnZoomOut);

        btnPrevious = new QPushButton(w_structview);
        btnPrevious->setObjectName(QString::fromUtf8("btnPrevious"));
        btnPrevious->setMinimumSize(QSize(0, 16));

        horizontalLayout_3->addWidget(btnPrevious);

        lblPage = new QSpinBox(w_structview);
        lblPage->setObjectName(QString::fromUtf8("lblPage"));

        horizontalLayout_3->addWidget(lblPage);

        label_2 = new QLabel(w_structview);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy5);
        label_2->setMinimumSize(QSize(0, 16));

        horizontalLayout_3->addWidget(label_2);

        lblPageEnd = new QLabel(w_structview);
        lblPageEnd->setObjectName(QString::fromUtf8("lblPageEnd"));
        lblPageEnd->setMinimumSize(QSize(0, 16));
        lblPageEnd->setFrameShape(QFrame::Box);

        horizontalLayout_3->addWidget(lblPageEnd);

        btnNext = new QPushButton(w_structview);
        btnNext->setObjectName(QString::fromUtf8("btnNext"));
        btnNext->setMinimumSize(QSize(0, 16));

        horizontalLayout_3->addWidget(btnNext);

        btnClearPainter = new QPushButton(w_structview);
        btnClearPainter->setObjectName(QString::fromUtf8("btnClearPainter"));

        horizontalLayout_3->addWidget(btnClearPainter);

        btnFull = new QPushButton(w_structview);
        btnFull->setObjectName(QString::fromUtf8("btnFull"));

        horizontalLayout_3->addWidget(btnFull);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        verticalLayout->addLayout(horizontalLayout_2);

        scrollArea = new QScrollArea(w_structview);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setLineWidth(0);
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 937, 817));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        listErrors = new QListWidget(w_structview);
        listErrors->setObjectName(QString::fromUtf8("listErrors"));
        QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(listErrors->sizePolicy().hasHeightForWidth());
        listErrors->setSizePolicy(sizePolicy6);
        listErrors->setMinimumSize(QSize(500, 100));
        listErrors->setMaximumSize(QSize(500, 100));

        horizontalLayout_4->addWidget(listErrors);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        btnDeleteSelectedItem = new QPushButton(w_structview);
        btnDeleteSelectedItem->setObjectName(QString::fromUtf8("btnDeleteSelectedItem"));

        verticalLayout_6->addWidget(btnDeleteSelectedItem);

        btnViewHtml = new QPushButton(w_structview);
        btnViewHtml->setObjectName(QString::fromUtf8("btnViewHtml"));

        verticalLayout_6->addWidget(btnViewHtml);


        horizontalLayout_4->addLayout(verticalLayout_6);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        lbl_blocking = new QLabel(w_structview);
        lbl_blocking->setObjectName(QString::fromUtf8("lbl_blocking"));

        verticalLayout_4->addWidget(lbl_blocking);

        lbl_major = new QLabel(w_structview);
        lbl_major->setObjectName(QString::fromUtf8("lbl_major"));

        verticalLayout_4->addWidget(lbl_major);

        lbl_minor = new QLabel(w_structview);
        lbl_minor->setObjectName(QString::fromUtf8("lbl_minor"));

        verticalLayout_4->addWidget(lbl_minor);


        horizontalLayout_4->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        btnError = new QPushButton(w_structview);
        btnError->setObjectName(QString::fromUtf8("btnError"));

        verticalLayout_5->addWidget(btnError);

        btnStructure = new QPushButton(w_structview);
        btnStructure->setObjectName(QString::fromUtf8("btnStructure"));

        verticalLayout_5->addWidget(btnStructure);

        btnViewMets = new QPushButton(w_structview);
        btnViewMets->setObjectName(QString::fromUtf8("btnViewMets"));

        verticalLayout_5->addWidget(btnViewMets);

        btnViewDir = new QPushButton(w_structview);
        btnViewDir->setObjectName(QString::fromUtf8("btnViewDir"));

        verticalLayout_5->addWidget(btnViewDir);


        horizontalLayout_4->addLayout(verticalLayout_5);


        verticalLayout_2->addLayout(horizontalLayout_4);


        retranslateUi(w_structview);

        QMetaObject::connectSlotsByName(w_structview);
    } // setupUi

    void retranslateUi(QWidget *w_structview)
    {
        w_structview->setWindowTitle(QCoreApplication::translate("w_structview", "Form", nullptr));
        label->setText(QCoreApplication::translate("w_structview", "Please select calendar entry for Issue", nullptr));
        btnUndo->setText(QCoreApplication::translate("w_structview", "Undo", nullptr));
        btnChecked->setText(QCoreApplication::translate("w_structview", "Checked", nullptr));
        btnZoomIn->setText(QCoreApplication::translate("w_structview", "Zoom In", nullptr));
        zoomNormal->setText(QCoreApplication::translate("w_structview", "100%", nullptr));
        btnZoomOut->setText(QCoreApplication::translate("w_structview", "Zoom Out", nullptr));
        btnPrevious->setText(QCoreApplication::translate("w_structview", "<", nullptr));
        label_2->setText(QCoreApplication::translate("w_structview", "  /", nullptr));
        lblPageEnd->setText(QString());
        btnNext->setText(QCoreApplication::translate("w_structview", ">", nullptr));
        btnClearPainter->setText(QCoreApplication::translate("w_structview", "Clear highlighting", nullptr));
        btnFull->setText(QCoreApplication::translate("w_structview", "Full", nullptr));
        btnDeleteSelectedItem->setText(QCoreApplication::translate("w_structview", "Delete Selected Error Item", nullptr));
        btnViewHtml->setText(QCoreApplication::translate("w_structview", "View All Batch Errors", nullptr));
        lbl_blocking->setText(QCoreApplication::translate("w_structview", "Blocking :", nullptr));
        lbl_major->setText(QCoreApplication::translate("w_structview", "Major :", nullptr));
        lbl_minor->setText(QCoreApplication::translate("w_structview", "Minor :", nullptr));
        btnError->setText(QCoreApplication::translate("w_structview", " Error", nullptr));
        btnStructure->setText(QCoreApplication::translate("w_structview", "Structure", nullptr));
        btnViewMets->setText(QCoreApplication::translate("w_structview", "View Mets File", nullptr));
        btnViewDir->setText(QCoreApplication::translate("w_structview", "View Mets Dir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class w_structview: public Ui_w_structview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_STRUCTVIEW_H
