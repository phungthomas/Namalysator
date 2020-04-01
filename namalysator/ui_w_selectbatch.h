/********************************************************************************
** Form generated from reading UI file 'w_selectbatch.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_SELECTBATCH_H
#define UI_W_SELECTBATCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_w_selectBatch
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QLabel *lbBatchName;
    QLabel *label_4;
    QLabel *lbYear;
    QLabel *label_7;
    QLabel *lbNumberMets;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupButton;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAnalyze;
    QPushButton *btnCancel;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_5;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_6;
    QTableWidget *tableSummary;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QTableView *paramView;
    QGroupBox *gbBatch;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnBrowseDb;
    QLabel *label;
    QLineEdit *lineEditSql;
    QLabel *label_8;
    QComboBox *cbBatchName;
    QLabel *label_2;
    QComboBox *cbSubBatchName;
    QLabel *label_9;
    QListWidget *listDateTestset;
    QLabel *label_10;
    QPushButton *btnPath;
    QLineEdit *lineEdit;

    void setupUi(QWidget *w_selectBatch)
    {
        if (w_selectBatch->objectName().isEmpty())
            w_selectBatch->setObjectName(QString::fromUtf8("w_selectBatch"));
        w_selectBatch->resize(869, 786);
        gridLayout = new QGridLayout(w_selectBatch);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(w_selectBatch);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(150, 0));
        groupBox->setMaximumSize(QSize(200, 16777215));
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_4->addWidget(label_3);

        lbBatchName = new QLabel(groupBox);
        lbBatchName->setObjectName(QString::fromUtf8("lbBatchName"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lbBatchName->setFont(font);

        verticalLayout_4->addWidget(lbBatchName);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_4->addWidget(label_4);

        lbYear = new QLabel(groupBox);
        lbYear->setObjectName(QString::fromUtf8("lbYear"));
        lbYear->setFont(font);

        verticalLayout_4->addWidget(lbYear);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_4->addWidget(label_7);

        lbNumberMets = new QLabel(groupBox);
        lbNumberMets->setObjectName(QString::fromUtf8("lbNumberMets"));
        lbNumberMets->setFont(font);

        verticalLayout_4->addWidget(lbNumberMets);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        gridLayout->addWidget(groupBox, 1, 0, 1, 1);

        groupButton = new QGroupBox(w_selectBatch);
        groupButton->setObjectName(QString::fromUtf8("groupButton"));
        groupButton->setEnabled(false);
        horizontalLayout = new QHBoxLayout(groupButton);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnAnalyze = new QPushButton(groupButton);
        btnAnalyze->setObjectName(QString::fromUtf8("btnAnalyze"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(170, 170, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(212, 212, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(85, 85, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(113, 113, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(212, 212, 127, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        btnAnalyze->setPalette(palette);

        horizontalLayout->addWidget(btnAnalyze);

        btnCancel = new QPushButton(groupButton);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        gridLayout->addWidget(groupButton, 4, 1, 1, 1);

        groupBox_4 = new QGroupBox(w_selectBatch);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(0, 250));
        verticalLayout_5 = new QVBoxLayout(groupBox_4);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        scrollArea = new QScrollArea(groupBox_4);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setMinimumSize(QSize(0, 0));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 623, 241));
        verticalLayout_6 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        tableSummary = new QTableWidget(scrollAreaWidgetContents);
        tableSummary->setObjectName(QString::fromUtf8("tableSummary"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableSummary->sizePolicy().hasHeightForWidth());
        tableSummary->setSizePolicy(sizePolicy);
        tableSummary->setMinimumSize(QSize(100, 0));

        verticalLayout_6->addWidget(tableSummary);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_5->addWidget(scrollArea);


        gridLayout->addWidget(groupBox_4, 1, 1, 1, 1);

        groupBox_2 = new QGroupBox(w_selectBatch);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        paramView = new QTableView(groupBox_2);
        paramView->setObjectName(QString::fromUtf8("paramView"));
        paramView->setMinimumSize(QSize(100, 0));

        verticalLayout->addWidget(paramView);


        gridLayout->addWidget(groupBox_2, 0, 1, 1, 1);

        gbBatch = new QGroupBox(w_selectBatch);
        gbBatch->setObjectName(QString::fromUtf8("gbBatch"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gbBatch->sizePolicy().hasHeightForWidth());
        gbBatch->setSizePolicy(sizePolicy1);
        gbBatch->setMinimumSize(QSize(150, 0));
        gbBatch->setMaximumSize(QSize(200, 437));
        verticalLayout_2 = new QVBoxLayout(gbBatch);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        btnBrowseDb = new QPushButton(gbBatch);
        btnBrowseDb->setObjectName(QString::fromUtf8("btnBrowseDb"));

        verticalLayout_2->addWidget(btnBrowseDb);

        label = new QLabel(gbBatch);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        lineEditSql = new QLineEdit(gbBatch);
        lineEditSql->setObjectName(QString::fromUtf8("lineEditSql"));
        lineEditSql->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEditSql->sizePolicy().hasHeightForWidth());
        lineEditSql->setSizePolicy(sizePolicy2);
        lineEditSql->setMinimumSize(QSize(100, 0));

        verticalLayout_2->addWidget(lineEditSql);

        label_8 = new QLabel(gbBatch);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_2->addWidget(label_8);

        cbBatchName = new QComboBox(gbBatch);
        cbBatchName->setObjectName(QString::fromUtf8("cbBatchName"));
        cbBatchName->setEnabled(true);

        verticalLayout_2->addWidget(cbBatchName);

        label_2 = new QLabel(gbBatch);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        cbSubBatchName = new QComboBox(gbBatch);
        cbSubBatchName->setObjectName(QString::fromUtf8("cbSubBatchName"));

        verticalLayout_2->addWidget(cbSubBatchName);

        label_9 = new QLabel(gbBatch);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_2->addWidget(label_9);

        listDateTestset = new QListWidget(gbBatch);
        listDateTestset->setObjectName(QString::fromUtf8("listDateTestset"));

        verticalLayout_2->addWidget(listDateTestset);

        label_10 = new QLabel(gbBatch);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout_2->addWidget(label_10);

        btnPath = new QPushButton(gbBatch);
        btnPath->setObjectName(QString::fromUtf8("btnPath"));

        verticalLayout_2->addWidget(btnPath);

        lineEdit = new QLineEdit(gbBatch);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout_2->addWidget(lineEdit);


        gridLayout->addWidget(gbBatch, 0, 0, 1, 1);


        retranslateUi(w_selectBatch);

        QMetaObject::connectSlotsByName(w_selectBatch);
    } // setupUi

    void retranslateUi(QWidget *w_selectBatch)
    {
        w_selectBatch->setWindowTitle(QCoreApplication::translate("w_selectBatch", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("w_selectBatch", "Details", nullptr));
        label_3->setText(QCoreApplication::translate("w_selectBatch", "Batchname :", nullptr));
        lbBatchName->setText(QString());
        label_4->setText(QCoreApplication::translate("w_selectBatch", "Year on disk :", nullptr));
        lbYear->setText(QString());
        label_7->setText(QCoreApplication::translate("w_selectBatch", "Number of METS files :", nullptr));
        lbNumberMets->setText(QString());
        groupButton->setTitle(QString());
        btnAnalyze->setText(QCoreApplication::translate("w_selectBatch", "Go to disk analyze", nullptr));
        btnCancel->setText(QCoreApplication::translate("w_selectBatch", "Cancel", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("w_selectBatch", "Error summary", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("w_selectBatch", "Parameters", nullptr));
        gbBatch->setTitle(QCoreApplication::translate("w_selectBatch", "Batch", nullptr));
        btnBrowseDb->setText(QCoreApplication::translate("w_selectBatch", "Browse", nullptr));
        label->setText(QCoreApplication::translate("w_selectBatch", "Select database :", nullptr));
        lineEditSql->setText(QString());
        label_8->setText(QCoreApplication::translate("w_selectBatch", "Batch Name", nullptr));
        label_2->setText(QCoreApplication::translate("w_selectBatch", "Sub Batch Name", nullptr));
        label_9->setText(QCoreApplication::translate("w_selectBatch", "Batch Test on date :", nullptr));
        label_10->setText(QCoreApplication::translate("w_selectBatch", "Path of the disk :", nullptr));
        btnPath->setText(QCoreApplication::translate("w_selectBatch", "Browse", nullptr));
        lineEdit->setText(QCoreApplication::translate("w_selectBatch", "C:/", nullptr));
    } // retranslateUi

};

namespace Ui {
    class w_selectBatch: public Ui_w_selectBatch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_SELECTBATCH_H
