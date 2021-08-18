/********************************************************************************
** Form generated from reading UI file 'w_inventaire.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_INVENTAIRE_H
#define UI_W_INVENTAIRE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_w_inventaire
{
public:
    QTableWidget *table;
    QPushButton *btnViewIssue;
    QPushButton *btnInventaire;
    QComboBox *comboYear;
    QPushButton *btnExport;
    QGroupBox *groupBox;
    QTableWidget *tableClickMissing;
    QGroupBox *groupBox_2;
    QTableWidget *tableEnTrop;
    QGroupBox *groupBox_3;
    QTableWidget *tableMissingInventaire;
    QPushButton *btnShowErrors;

    void setupUi(QWidget *w_inventaire)
    {
        if (w_inventaire->objectName().isEmpty())
            w_inventaire->setObjectName(QString::fromUtf8("w_inventaire"));
        w_inventaire->resize(1047, 886);
        w_inventaire->setFocusPolicy(Qt::WheelFocus);
        table = new QTableWidget(w_inventaire);
        table->setObjectName(QString::fromUtf8("table"));
        table->setEnabled(true);
        table->setGeometry(QRect(40, 40, 941, 451));
        table->setFocusPolicy(Qt::WheelFocus);
        table->setSelectionMode(QAbstractItemView::SingleSelection);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        btnViewIssue = new QPushButton(w_inventaire);
        btnViewIssue->setObjectName(QString::fromUtf8("btnViewIssue"));
        btnViewIssue->setGeometry(QRect(330, 10, 75, 24));
        btnInventaire = new QPushButton(w_inventaire);
        btnInventaire->setObjectName(QString::fromUtf8("btnInventaire"));
        btnInventaire->setGeometry(QRect(440, 10, 91, 24));
        comboYear = new QComboBox(w_inventaire);
        comboYear->setObjectName(QString::fromUtf8("comboYear"));
        comboYear->setGeometry(QRect(40, 10, 131, 22));
        btnExport = new QPushButton(w_inventaire);
        btnExport->setObjectName(QString::fromUtf8("btnExport"));
        btnExport->setGeometry(QRect(600, 10, 75, 24));
        groupBox = new QGroupBox(w_inventaire);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 490, 961, 81));
        tableClickMissing = new QTableWidget(groupBox);
        tableClickMissing->setObjectName(QString::fromUtf8("tableClickMissing"));
        tableClickMissing->setGeometry(QRect(20, 20, 931, 51));
        groupBox_2 = new QGroupBox(w_inventaire);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 700, 961, 131));
        tableEnTrop = new QTableWidget(groupBox_2);
        tableEnTrop->setObjectName(QString::fromUtf8("tableEnTrop"));
        tableEnTrop->setGeometry(QRect(20, 20, 931, 101));
        groupBox_3 = new QGroupBox(w_inventaire);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(30, 570, 961, 131));
        tableMissingInventaire = new QTableWidget(groupBox_3);
        tableMissingInventaire->setObjectName(QString::fromUtf8("tableMissingInventaire"));
        tableMissingInventaire->setGeometry(QRect(20, 20, 931, 101));
        btnShowErrors = new QPushButton(w_inventaire);
        btnShowErrors->setObjectName(QString::fromUtf8("btnShowErrors"));
        btnShowErrors->setGeometry(QRect(190, 10, 111, 24));

        retranslateUi(w_inventaire);

        QMetaObject::connectSlotsByName(w_inventaire);
    } // setupUi

    void retranslateUi(QWidget *w_inventaire)
    {
        w_inventaire->setWindowTitle(QCoreApplication::translate("w_inventaire", "w_inventaire", nullptr));
        btnViewIssue->setText(QCoreApplication::translate("w_inventaire", "View issue", nullptr));
        btnInventaire->setText(QCoreApplication::translate("w_inventaire", "Show inventaire", nullptr));
        btnExport->setText(QCoreApplication::translate("w_inventaire", "Export ", nullptr));
        groupBox->setTitle(QCoreApplication::translate("w_inventaire", "Current line from inventory", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("w_inventaire", "Issues en trop", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("w_inventaire", "Missing from inventaire", nullptr));
        btnShowErrors->setText(QCoreApplication::translate("w_inventaire", "Show only errors", nullptr));
    } // retranslateUi

};

namespace Ui {
    class w_inventaire: public Ui_w_inventaire {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_INVENTAIRE_H
