/********************************************************************************
** Form generated from reading UI file 'w_screenshoterror.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_SCREENSHOTERROR_H
#define UI_W_SCREENSHOTERROR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_w_screenshoterror
{
public:
    QLabel *label;
    QGroupBox *groupBoxSaveError;
    QComboBox *comboBoxErrorType;
    QTextEdit *txtCommentaire;
    QPushButton *btnSave;
    QPushButton *btnClearPainter;
    QPushButton *btnClose;
    QPushButton *btnColor;
    QTextEdit *boxColor;
    QLabel *lbComment;

    void setupUi(QWidget *w_screenshoterror)
    {
        if (w_screenshoterror->objectName().isEmpty())
            w_screenshoterror->setObjectName(QString::fromUtf8("w_screenshoterror"));
        w_screenshoterror->resize(1144, 875);
        label = new QLabel(w_screenshoterror);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 291, 121));
        groupBoxSaveError = new QGroupBox(w_screenshoterror);
        groupBoxSaveError->setObjectName(QString::fromUtf8("groupBoxSaveError"));
        groupBoxSaveError->setEnabled(true);
        groupBoxSaveError->setGeometry(QRect(180, 790, 951, 61));
        comboBoxErrorType = new QComboBox(groupBoxSaveError);
        comboBoxErrorType->setObjectName(QString::fromUtf8("comboBoxErrorType"));
        comboBoxErrorType->setGeometry(QRect(20, 10, 241, 22));
        txtCommentaire = new QTextEdit(groupBoxSaveError);
        txtCommentaire->setObjectName(QString::fromUtf8("txtCommentaire"));
        txtCommentaire->setGeometry(QRect(270, 10, 491, 41));
        btnSave = new QPushButton(groupBoxSaveError);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));
        btnSave->setGeometry(QRect(790, 10, 101, 24));
        btnClearPainter = new QPushButton(w_screenshoterror);
        btnClearPainter->setObjectName(QString::fromUtf8("btnClearPainter"));
        btnClearPainter->setGeometry(QRect(90, 790, 75, 24));
        btnClose = new QPushButton(w_screenshoterror);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(90, 830, 75, 24));
        btnColor = new QPushButton(w_screenshoterror);
        btnColor->setObjectName(QString::fromUtf8("btnColor"));
        btnColor->setGeometry(QRect(10, 790, 75, 24));
        boxColor = new QTextEdit(w_screenshoterror);
        boxColor->setObjectName(QString::fromUtf8("boxColor"));
        boxColor->setEnabled(false);
        boxColor->setGeometry(QRect(20, 830, 41, 21));
        boxColor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        boxColor->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        lbComment = new QLabel(w_screenshoterror);
        lbComment->setObjectName(QString::fromUtf8("lbComment"));
        lbComment->setGeometry(QRect(190, 850, 661, 21));

        retranslateUi(w_screenshoterror);

        QMetaObject::connectSlotsByName(w_screenshoterror);
    } // setupUi

    void retranslateUi(QWidget *w_screenshoterror)
    {
        w_screenshoterror->setWindowTitle(QApplication::translate("w_screenshoterror", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("w_screenshoterror", "TextLabel", 0, QApplication::UnicodeUTF8));
        groupBoxSaveError->setTitle(QString());
        btnSave->setText(QApplication::translate("w_screenshoterror", "Save Image", 0, QApplication::UnicodeUTF8));
        btnClearPainter->setText(QApplication::translate("w_screenshoterror", "Clear painter", 0, QApplication::UnicodeUTF8));
        btnClose->setText(QApplication::translate("w_screenshoterror", "Close", 0, QApplication::UnicodeUTF8));
        btnColor->setText(QApplication::translate("w_screenshoterror", "Color", 0, QApplication::UnicodeUTF8));
        lbComment->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class w_screenshoterror: public Ui_w_screenshoterror {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_SCREENSHOTERROR_H
