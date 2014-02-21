/********************************************************************************
** Form generated from reading UI file 'w_selectbatch.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_SELECTBATCH_H
#define UI_W_SELECTBATCH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_w_selectBatch
{
public:
    QGroupBox *gbBatch;
    QComboBox *cbBatchName;
    QLabel *label_8;
    QLabel *label_9;
    QListWidget *listDateTestset;
    QLabel *label_10;
    QLineEdit *lineEdit;
    QPushButton *btnPath;
    QLabel *label;
    QPushButton *btnBrowseDb;
    QLineEdit *lineEditSql;
    QGroupBox *groupBox;
    QLabel *label_3;
    QLabel *lbBatchName;
    QLabel *label_4;
    QLabel *lbYear;
    QLabel *label_7;
    QLabel *lbNumberMets;
    QGroupBox *groupButton;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAnalyze;
    QPushButton *btnCancel;
    QGroupBox *groupBox_2;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_11;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_12;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *lbschema;
    QLabel *lbFileCheck;
    QLabel *lbChecksum;
    QLabel *lbDivs;
    QLabel *lbUnlinkedIdentifier;
    QLabel *lbIdentifierMix;
    QLabel *lbAltoBlockPerpage;
    QLabel *lbBlockStructure;
    QLabel *lbCoverageAlto;
    QLabel *lbInvalidSupplement;
    QLabel *lbMultipleBlockUse;
    QLabel *label_20;
    QLabel *lbPages;
    QLabel *label_21;
    QLabel *lbDateFolderIssue;
    QLabel *label_22;
    QLabel *lbNoIssueDef;
    QTableWidget *tableSummary;
    QGroupBox *groupBox_3;
    QLabel *label_19;
    QLineEdit *lineEditInventaire;
    QPushButton *btnBrowseDbInventaire;
    QComboBox *cbInventaire;

    void setupUi(QWidget *w_selectBatch)
    {
        if (w_selectBatch->objectName().isEmpty())
            w_selectBatch->setObjectName(QString::fromUtf8("w_selectBatch"));
        w_selectBatch->resize(775, 639);
        gbBatch = new QGroupBox(w_selectBatch);
        gbBatch->setObjectName(QString::fromUtf8("gbBatch"));
        gbBatch->setGeometry(QRect(30, 30, 271, 261));
        cbBatchName = new QComboBox(gbBatch);
        cbBatchName->setObjectName(QString::fromUtf8("cbBatchName"));
        cbBatchName->setEnabled(true);
        cbBatchName->setGeometry(QRect(10, 90, 151, 22));
        label_8 = new QLabel(gbBatch);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 70, 61, 16));
        label_9 = new QLabel(gbBatch);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 110, 131, 21));
        listDateTestset = new QListWidget(gbBatch);
        listDateTestset->setObjectName(QString::fromUtf8("listDateTestset"));
        listDateTestset->setGeometry(QRect(10, 140, 231, 51));
        label_10 = new QLabel(gbBatch);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 200, 81, 21));
        lineEdit = new QLineEdit(gbBatch);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 230, 231, 20));
        btnPath = new QPushButton(gbBatch);
        btnPath->setObjectName(QString::fromUtf8("btnPath"));
        btnPath->setGeometry(QRect(110, 201, 71, 20));
        label = new QLabel(gbBatch);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 91, 16));
        btnBrowseDb = new QPushButton(gbBatch);
        btnBrowseDb->setObjectName(QString::fromUtf8("btnBrowseDb"));
        btnBrowseDb->setGeometry(QRect(100, 20, 61, 21));
        lineEditSql = new QLineEdit(gbBatch);
        lineEditSql->setObjectName(QString::fromUtf8("lineEditSql"));
        lineEditSql->setEnabled(true);
        lineEditSql->setGeometry(QRect(10, 50, 231, 20));
        groupBox = new QGroupBox(w_selectBatch);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 400, 271, 151));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(11, 25, 60, 16));
        lbBatchName = new QLabel(groupBox);
        lbBatchName->setObjectName(QString::fromUtf8("lbBatchName"));
        lbBatchName->setGeometry(QRect(11, 45, 261, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lbBatchName->setFont(font);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(11, 65, 64, 16));
        lbYear = new QLabel(groupBox);
        lbYear->setObjectName(QString::fromUtf8("lbYear"));
        lbYear->setGeometry(QRect(11, 85, 261, 16));
        lbYear->setFont(font);
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(11, 105, 108, 16));
        lbNumberMets = new QLabel(groupBox);
        lbNumberMets->setObjectName(QString::fromUtf8("lbNumberMets"));
        lbNumberMets->setGeometry(QRect(11, 125, 261, 16));
        lbNumberMets->setFont(font);
        groupButton = new QGroupBox(w_selectBatch);
        groupButton->setObjectName(QString::fromUtf8("groupButton"));
        groupButton->setEnabled(false);
        groupButton->setGeometry(QRect(30, 560, 251, 46));
        horizontalLayout = new QHBoxLayout(groupButton);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnAnalyze = new QPushButton(groupButton);
        btnAnalyze->setObjectName(QString::fromUtf8("btnAnalyze"));

        horizontalLayout->addWidget(btnAnalyze);

        btnCancel = new QPushButton(groupButton);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout->addWidget(btnCancel);

        groupBox_2 = new QGroupBox(w_selectBatch);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(310, 30, 231, 321));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 20, 91, 16));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 40, 81, 16));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 60, 91, 16));
        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 80, 91, 16));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(20, 120, 91, 16));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(20, 140, 101, 16));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(20, 100, 91, 16));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 160, 91, 16));
        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(20, 180, 151, 16));
        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(20, 200, 151, 16));
        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(20, 220, 141, 16));
        lbschema = new QLabel(groupBox_2);
        lbschema->setObjectName(QString::fromUtf8("lbschema"));
        lbschema->setGeometry(QRect(160, 20, 46, 16));
        lbFileCheck = new QLabel(groupBox_2);
        lbFileCheck->setObjectName(QString::fromUtf8("lbFileCheck"));
        lbFileCheck->setGeometry(QRect(160, 40, 51, 20));
        lbChecksum = new QLabel(groupBox_2);
        lbChecksum->setObjectName(QString::fromUtf8("lbChecksum"));
        lbChecksum->setGeometry(QRect(160, 60, 46, 16));
        lbDivs = new QLabel(groupBox_2);
        lbDivs->setObjectName(QString::fromUtf8("lbDivs"));
        lbDivs->setGeometry(QRect(160, 80, 46, 14));
        lbUnlinkedIdentifier = new QLabel(groupBox_2);
        lbUnlinkedIdentifier->setObjectName(QString::fromUtf8("lbUnlinkedIdentifier"));
        lbUnlinkedIdentifier->setGeometry(QRect(160, 94, 46, 20));
        lbIdentifierMix = new QLabel(groupBox_2);
        lbIdentifierMix->setObjectName(QString::fromUtf8("lbIdentifierMix"));
        lbIdentifierMix->setGeometry(QRect(160, 120, 46, 14));
        lbAltoBlockPerpage = new QLabel(groupBox_2);
        lbAltoBlockPerpage->setObjectName(QString::fromUtf8("lbAltoBlockPerpage"));
        lbAltoBlockPerpage->setGeometry(QRect(160, 140, 46, 16));
        lbBlockStructure = new QLabel(groupBox_2);
        lbBlockStructure->setObjectName(QString::fromUtf8("lbBlockStructure"));
        lbBlockStructure->setGeometry(QRect(160, 160, 46, 14));
        lbCoverageAlto = new QLabel(groupBox_2);
        lbCoverageAlto->setObjectName(QString::fromUtf8("lbCoverageAlto"));
        lbCoverageAlto->setGeometry(QRect(160, 180, 46, 14));
        lbInvalidSupplement = new QLabel(groupBox_2);
        lbInvalidSupplement->setObjectName(QString::fromUtf8("lbInvalidSupplement"));
        lbInvalidSupplement->setGeometry(QRect(160, 220, 46, 14));
        lbMultipleBlockUse = new QLabel(groupBox_2);
        lbMultipleBlockUse->setObjectName(QString::fromUtf8("lbMultipleBlockUse"));
        lbMultipleBlockUse->setGeometry(QRect(160, 200, 46, 14));
        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(20, 240, 81, 16));
        lbPages = new QLabel(groupBox_2);
        lbPages->setObjectName(QString::fromUtf8("lbPages"));
        lbPages->setGeometry(QRect(160, 240, 41, 20));
        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(20, 260, 101, 16));
        lbDateFolderIssue = new QLabel(groupBox_2);
        lbDateFolderIssue->setObjectName(QString::fromUtf8("lbDateFolderIssue"));
        lbDateFolderIssue->setGeometry(QRect(160, 260, 41, 20));
        label_22 = new QLabel(groupBox_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(20, 280, 91, 16));
        lbNoIssueDef = new QLabel(groupBox_2);
        lbNoIssueDef->setObjectName(QString::fromUtf8("lbNoIssueDef"));
        lbNoIssueDef->setGeometry(QRect(160, 280, 46, 14));
        tableSummary = new QTableWidget(w_selectBatch);
        tableSummary->setObjectName(QString::fromUtf8("tableSummary"));
        tableSummary->setGeometry(QRect(310, 360, 231, 191));
        tableSummary->setEditTriggers(QAbstractItemView::NoEditTriggers);
        groupBox_3 = new QGroupBox(w_selectBatch);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(29, 290, 271, 111));
        label_19 = new QLabel(groupBox_3);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(10, 20, 221, 20));
        lineEditInventaire = new QLineEdit(groupBox_3);
        lineEditInventaire->setObjectName(QString::fromUtf8("lineEditInventaire"));
        lineEditInventaire->setGeometry(QRect(10, 50, 231, 20));
        btnBrowseDbInventaire = new QPushButton(groupBox_3);
        btnBrowseDbInventaire->setObjectName(QString::fromUtf8("btnBrowseDbInventaire"));
        btnBrowseDbInventaire->setGeometry(QRect(110, 16, 75, 20));
        cbInventaire = new QComboBox(groupBox_3);
        cbInventaire->setObjectName(QString::fromUtf8("cbInventaire"));
        cbInventaire->setEnabled(true);
        cbInventaire->setGeometry(QRect(10, 82, 151, 20));

        retranslateUi(w_selectBatch);

        QMetaObject::connectSlotsByName(w_selectBatch);
    } // setupUi

    void retranslateUi(QWidget *w_selectBatch)
    {
        w_selectBatch->setWindowTitle(QApplication::translate("w_selectBatch", "Form", 0, QApplication::UnicodeUTF8));
        gbBatch->setTitle(QApplication::translate("w_selectBatch", "Batch", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("w_selectBatch", "Batch Name", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("w_selectBatch", "Batch Test on date :", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("w_selectBatch", "Path of the disk :", 0, QApplication::UnicodeUTF8));
        lineEdit->setText(QApplication::translate("w_selectBatch", "C:/", 0, QApplication::UnicodeUTF8));
        btnPath->setText(QApplication::translate("w_selectBatch", "Browse", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("w_selectBatch", "Select database :", 0, QApplication::UnicodeUTF8));
        btnBrowseDb->setText(QApplication::translate("w_selectBatch", "Browse", 0, QApplication::UnicodeUTF8));
        lineEditSql->setText(QString());
        groupBox->setTitle(QApplication::translate("w_selectBatch", "Details", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("w_selectBatch", "Batchname :", 0, QApplication::UnicodeUTF8));
        lbBatchName->setText(QString());
        label_4->setText(QApplication::translate("w_selectBatch", "Year on disk :", 0, QApplication::UnicodeUTF8));
        lbYear->setText(QString());
        label_7->setText(QApplication::translate("w_selectBatch", "Number of METS files :", 0, QApplication::UnicodeUTF8));
        lbNumberMets->setText(QString());
        groupButton->setTitle(QString());
        btnAnalyze->setText(QApplication::translate("w_selectBatch", "Go to disk analyze", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("w_selectBatch", "Cancel", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("w_selectBatch", "Parameters", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("w_selectBatch", "Schemavalidation", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("w_selectBatch", "File check", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("w_selectBatch", "Checksum", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("w_selectBatch", "Divs", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("w_selectBatch", "Identifiermix", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("w_selectBatch", "Altoblockperpage", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("w_selectBatch", "Unlinked identifier", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("w_selectBatch", "Block structure", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("w_selectBatch", "Coveragepercentageperalto", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("w_selectBatch", "Multiple block use", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("w_selectBatch", "Invalid Supplement", 0, QApplication::UnicodeUTF8));
        lbschema->setText(QString());
        lbFileCheck->setText(QString());
        lbChecksum->setText(QString());
        lbDivs->setText(QString());
        lbUnlinkedIdentifier->setText(QString());
        lbIdentifierMix->setText(QString());
        lbAltoBlockPerpage->setText(QString());
        lbBlockStructure->setText(QString());
        lbCoverageAlto->setText(QString());
        lbInvalidSupplement->setText(QString());
        lbMultipleBlockUse->setText(QString());
        label_20->setText(QApplication::translate("w_selectBatch", "Odds pages", 0, QApplication::UnicodeUTF8));
        lbPages->setText(QString());
        label_21->setText(QApplication::translate("w_selectBatch", "Date Folder - Issue", 0, QApplication::UnicodeUTF8));
        lbDateFolderIssue->setText(QString());
        label_22->setText(QApplication::translate("w_selectBatch", "No issue defined", 0, QApplication::UnicodeUTF8));
        lbNoIssueDef->setText(QString());
        groupBox_3->setTitle(QApplication::translate("w_selectBatch", "Inventaire", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("w_selectBatch", "Select database :", 0, QApplication::UnicodeUTF8));
        lineEditInventaire->setText(QString());
        btnBrowseDbInventaire->setText(QApplication::translate("w_selectBatch", "Browse", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class w_selectBatch: public Ui_w_selectBatch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_SELECTBATCH_H
