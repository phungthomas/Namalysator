/********************************************************************************
** Form generated from reading UI file 'w_summaryerrors.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_SUMMARYERRORS_H
#define UI_W_SUMMARYERRORS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_w_summaryerrors
{
public:
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_9;
    QLabel *label_3;
    QLabel *lbTotal;
    QLabel *lbTitles;
    QLabel *lbSummary;
    QLabel *lbDate;
    QTableWidget *tableYear;
    QSpacerItem *horizontalSpacer_3;
    QTableWidget *tableSummary;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *lbCorrectIssues;
    QLabel *lbTotal2;
    QLabel *lbPercent;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *w_summaryerrors)
    {
        if (w_summaryerrors->objectName().isEmpty())
            w_summaryerrors->setObjectName(QString::fromUtf8("w_summaryerrors"));
        w_summaryerrors->resize(957, 632);
        verticalLayout_5 = new QVBoxLayout(w_summaryerrors);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(w_summaryerrors);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout_2 = new QFormLayout(groupBox);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_9);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_3);

        lbTotal = new QLabel(groupBox);
        lbTotal->setObjectName(QString::fromUtf8("lbTotal"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, lbTotal);

        lbTitles = new QLabel(groupBox);
        lbTitles->setObjectName(QString::fromUtf8("lbTitles"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, lbTitles);

        lbSummary = new QLabel(groupBox);
        lbSummary->setObjectName(QString::fromUtf8("lbSummary"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lbSummary);

        lbDate = new QLabel(groupBox);
        lbDate->setObjectName(QString::fromUtf8("lbDate"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lbDate);

        label->raise();
        label->raise();
        label_2->raise();
        label_9->raise();
        label_3->raise();
        lbTotal->raise();
        lbTitles->raise();
        lbSummary->raise();
        lbDate->raise();

        verticalLayout->addWidget(groupBox);


        horizontalLayout->addLayout(verticalLayout);

        tableYear = new QTableWidget(w_summaryerrors);
        tableYear->setObjectName(QString::fromUtf8("tableYear"));
        tableYear->setMinimumSize(QSize(500, 0));

        horizontalLayout->addWidget(tableYear);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_5->addLayout(horizontalLayout);

        tableSummary = new QTableWidget(w_summaryerrors);
        if (tableSummary->columnCount() < 6)
            tableSummary->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableSummary->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableSummary->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableSummary->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableSummary->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableSummary->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableSummary->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableSummary->setObjectName(QString::fromUtf8("tableSummary"));
        tableSummary->setEnabled(true);
        tableSummary->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout_5->addWidget(tableSummary);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        groupBox_2 = new QGroupBox(w_summaryerrors);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        formLayout = new QFormLayout(groupBox_2);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_6);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_7);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_8);

        lbCorrectIssues = new QLabel(groupBox_2);
        lbCorrectIssues->setObjectName(QString::fromUtf8("lbCorrectIssues"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lbCorrectIssues);

        lbTotal2 = new QLabel(groupBox_2);
        lbTotal2->setObjectName(QString::fromUtf8("lbTotal2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lbTotal2);

        lbPercent = new QLabel(groupBox_2);
        lbPercent->setObjectName(QString::fromUtf8("lbPercent"));

        formLayout->setWidget(5, QFormLayout::FieldRole, lbPercent);


        horizontalLayout_2->addWidget(groupBox_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_2);


        retranslateUi(w_summaryerrors);

        QMetaObject::connectSlotsByName(w_summaryerrors);
    } // setupUi

    void retranslateUi(QWidget *w_summaryerrors)
    {
        w_summaryerrors->setWindowTitle(QCoreApplication::translate("w_summaryerrors", "Form", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("w_summaryerrors", "Summary of disk :", nullptr));
        label_2->setText(QCoreApplication::translate("w_summaryerrors", "Date of test :", nullptr));
        label_9->setText(QCoreApplication::translate("w_summaryerrors", "Titles to correct :", nullptr));
        label_3->setText(QCoreApplication::translate("w_summaryerrors", "Number of Mets files :", nullptr));
        lbTotal->setText(QCoreApplication::translate("w_summaryerrors", "Total", nullptr));
        lbTitles->setText(QCoreApplication::translate("w_summaryerrors", "lbTitles", nullptr));
        lbSummary->setText(QCoreApplication::translate("w_summaryerrors", "TextLabel", nullptr));
        lbDate->setText(QCoreApplication::translate("w_summaryerrors", "TextLabel", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableSummary->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("w_summaryerrors", "Severity", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableSummary->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("w_summaryerrors", "Error category", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableSummary->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("w_summaryerrors", "Count", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableSummary->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("w_summaryerrors", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableSummary->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("w_summaryerrors", "Percentage", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableSummary->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("w_summaryerrors", "Details on sheet", nullptr));
        groupBox_2->setTitle(QString());
        label_6->setText(QCoreApplication::translate("w_summaryerrors", "Total number of issues :", nullptr));
        label_7->setText(QCoreApplication::translate("w_summaryerrors", "Correct issues :", nullptr));
        label_8->setText(QCoreApplication::translate("w_summaryerrors", "Percentage of correct issues :", nullptr));
        lbCorrectIssues->setText(QCoreApplication::translate("w_summaryerrors", "TextLabel", nullptr));
        lbTotal2->setText(QCoreApplication::translate("w_summaryerrors", "TextLabel", nullptr));
        lbPercent->setText(QCoreApplication::translate("w_summaryerrors", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class w_summaryerrors: public Ui_w_summaryerrors {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_SUMMARYERRORS_H
