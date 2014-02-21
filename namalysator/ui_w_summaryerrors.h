/********************************************************************************
** Form generated from reading UI file 'w_summaryerrors.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_SUMMARYERRORS_H
#define UI_W_SUMMARYERRORS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_w_summaryerrors
{
public:
    QTableWidget *tableSummary;
    QLabel *label_4;
    QLabel *label_5;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_9;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *lbSummary;
    QLabel *lbDate;
    QLabel *lbTotal;
    QLabel *lbTitles;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_4;
    QLabel *lbTotal2;
    QLabel *lbCorrectIssues;
    QLabel *lbPercent;
    QTableWidget *tableYear;

    void setupUi(QWidget *w_summaryerrors)
    {
        if (w_summaryerrors->objectName().isEmpty())
            w_summaryerrors->setObjectName(QString::fromUtf8("w_summaryerrors"));
        w_summaryerrors->resize(913, 629);
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
        tableSummary->setGeometry(QRect(60, 200, 761, 231));
        tableSummary->setEditTriggers(QAbstractItemView::NoEditTriggers);
        label_4 = new QLabel(w_summaryerrors);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(70, 170, 91, 16));
        label_5 = new QLabel(w_summaryerrors);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(190, 170, 46, 14));
        layoutWidget = new QWidget(w_summaryerrors);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 10, 107, 91));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout->addWidget(label_9);

        layoutWidget1 = new QWidget(w_summaryerrors);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(170, 10, 121, 91));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lbSummary = new QLabel(layoutWidget1);
        lbSummary->setObjectName(QString::fromUtf8("lbSummary"));

        verticalLayout_2->addWidget(lbSummary);

        lbDate = new QLabel(layoutWidget1);
        lbDate->setObjectName(QString::fromUtf8("lbDate"));

        verticalLayout_2->addWidget(lbDate);

        lbTotal = new QLabel(layoutWidget1);
        lbTotal->setObjectName(QString::fromUtf8("lbTotal"));

        verticalLayout_2->addWidget(lbTotal);

        lbTitles = new QLabel(layoutWidget1);
        lbTitles->setObjectName(QString::fromUtf8("lbTitles"));

        verticalLayout_2->addWidget(lbTitles);

        layoutWidget2 = new QWidget(w_summaryerrors);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(80, 440, 146, 56));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_3->addWidget(label_6);

        label_7 = new QLabel(layoutWidget2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_3->addWidget(label_7);

        label_8 = new QLabel(layoutWidget2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_3->addWidget(label_8);

        layoutWidget3 = new QWidget(w_summaryerrors);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(240, 440, 48, 56));
        verticalLayout_4 = new QVBoxLayout(layoutWidget3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        lbTotal2 = new QLabel(layoutWidget3);
        lbTotal2->setObjectName(QString::fromUtf8("lbTotal2"));

        verticalLayout_4->addWidget(lbTotal2);

        lbCorrectIssues = new QLabel(layoutWidget3);
        lbCorrectIssues->setObjectName(QString::fromUtf8("lbCorrectIssues"));

        verticalLayout_4->addWidget(lbCorrectIssues);

        lbPercent = new QLabel(layoutWidget3);
        lbPercent->setObjectName(QString::fromUtf8("lbPercent"));

        verticalLayout_4->addWidget(lbPercent);

        tableYear = new QTableWidget(w_summaryerrors);
        tableYear->setObjectName(QString::fromUtf8("tableYear"));
        tableYear->setGeometry(QRect(310, 10, 251, 151));

        retranslateUi(w_summaryerrors);

        QMetaObject::connectSlotsByName(w_summaryerrors);
    } // setupUi

    void retranslateUi(QWidget *w_summaryerrors)
    {
        w_summaryerrors->setWindowTitle(QApplication::translate("w_summaryerrors", "Form", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableSummary->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("w_summaryerrors", "Severity", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableSummary->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("w_summaryerrors", "Error category", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableSummary->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("w_summaryerrors", "Count", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableSummary->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("w_summaryerrors", "New Column", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableSummary->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("w_summaryerrors", "Percentage", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableSummary->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("w_summaryerrors", "Details on sheet", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("w_summaryerrors", "Title to correct", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("w_summaryerrors", "TextLabel", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("w_summaryerrors", "Summary of disk :", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("w_summaryerrors", "Date of test :", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("w_summaryerrors", "Number of Mets files :", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("w_summaryerrors", "Titles to correct :", 0, QApplication::UnicodeUTF8));
        lbSummary->setText(QApplication::translate("w_summaryerrors", "TextLabel", 0, QApplication::UnicodeUTF8));
        lbDate->setText(QApplication::translate("w_summaryerrors", "TextLabel", 0, QApplication::UnicodeUTF8));
        lbTotal->setText(QApplication::translate("w_summaryerrors", "Total", 0, QApplication::UnicodeUTF8));
        lbTitles->setText(QApplication::translate("w_summaryerrors", "lbTitles", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("w_summaryerrors", "Total number of issues :", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("w_summaryerrors", "Correct issues :", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("w_summaryerrors", "Percentage of correct issues :", 0, QApplication::UnicodeUTF8));
        lbTotal2->setText(QApplication::translate("w_summaryerrors", "TextLabel", 0, QApplication::UnicodeUTF8));
        lbCorrectIssues->setText(QApplication::translate("w_summaryerrors", "TextLabel", 0, QApplication::UnicodeUTF8));
        lbPercent->setText(QApplication::translate("w_summaryerrors", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class w_summaryerrors: public Ui_w_summaryerrors {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_SUMMARYERRORS_H
