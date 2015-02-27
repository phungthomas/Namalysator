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
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_w_screenshoterror
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QPushButton *btnSave;
    QPushButton *btnColor;
    QTextEdit *boxColor;
    QPushButton *btnClearPainter;
    QPushButton *btnClose;
    QTextEdit *txtCommentaire;
    QComboBox *comboBoxErrorType;
    QLabel *lbComment;
    QLabel *label_2;
    QLineEdit *customEdit;

    void setupUi(QWidget *w_screenshoterror)
    {
        if (w_screenshoterror->objectName().isEmpty())
            w_screenshoterror->setObjectName(QString::fromUtf8("w_screenshoterror"));
        w_screenshoterror->resize(954, 860);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(w_screenshoterror->sizePolicy().hasHeightForWidth());
        w_screenshoterror->setSizePolicy(sizePolicy);
        w_screenshoterror->setMinimumSize(QSize(300, 300));
        verticalLayout_2 = new QVBoxLayout(w_screenshoterror);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        label = new QLabel(w_screenshoterror);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(0, 550));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btnSave = new QPushButton(w_screenshoterror);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        gridLayout->addWidget(btnSave, 0, 3, 1, 1);

        btnColor = new QPushButton(w_screenshoterror);
        btnColor->setObjectName(QString::fromUtf8("btnColor"));

        gridLayout->addWidget(btnColor, 0, 0, 1, 1);

        boxColor = new QTextEdit(w_screenshoterror);
        boxColor->setObjectName(QString::fromUtf8("boxColor"));
        boxColor->setEnabled(false);
        boxColor->setMinimumSize(QSize(10, 10));
        boxColor->setMaximumSize(QSize(60, 20));
        boxColor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        boxColor->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout->addWidget(boxColor, 2, 0, 1, 1);

        btnClearPainter = new QPushButton(w_screenshoterror);
        btnClearPainter->setObjectName(QString::fromUtf8("btnClearPainter"));

        gridLayout->addWidget(btnClearPainter, 0, 1, 1, 1);

        btnClose = new QPushButton(w_screenshoterror);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));

        gridLayout->addWidget(btnClose, 2, 3, 1, 1);

        txtCommentaire = new QTextEdit(w_screenshoterror);
        txtCommentaire->setObjectName(QString::fromUtf8("txtCommentaire"));
        txtCommentaire->setMinimumSize(QSize(10, 0));
        txtCommentaire->setMaximumSize(QSize(16777215, 120));

        gridLayout->addWidget(txtCommentaire, 2, 2, 1, 1);

        comboBoxErrorType = new QComboBox(w_screenshoterror);
        comboBoxErrorType->setObjectName(QString::fromUtf8("comboBoxErrorType"));

        gridLayout->addWidget(comboBoxErrorType, 0, 2, 1, 1);

        lbComment = new QLabel(w_screenshoterror);
        lbComment->setObjectName(QString::fromUtf8("lbComment"));

        gridLayout->addWidget(lbComment, 3, 2, 1, 1);

        label_2 = new QLabel(w_screenshoterror);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        customEdit = new QLineEdit(w_screenshoterror);
        customEdit->setObjectName(QString::fromUtf8("customEdit"));

        gridLayout->addWidget(customEdit, 1, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(w_screenshoterror);

        QMetaObject::connectSlotsByName(w_screenshoterror);
    } // setupUi

    void retranslateUi(QWidget *w_screenshoterror)
    {
        w_screenshoterror->setWindowTitle(QApplication::translate("w_screenshoterror", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("w_screenshoterror", "TextLabel", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("w_screenshoterror", "Save Image", 0, QApplication::UnicodeUTF8));
        btnColor->setText(QApplication::translate("w_screenshoterror", "Color", 0, QApplication::UnicodeUTF8));
        btnClearPainter->setText(QApplication::translate("w_screenshoterror", "Clear painter", 0, QApplication::UnicodeUTF8));
        btnClose->setText(QApplication::translate("w_screenshoterror", "Close", 0, QApplication::UnicodeUTF8));
        lbComment->setText(QString());
        label_2->setText(QApplication::translate("w_screenshoterror", "Only for CUSTOM", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class w_screenshoterror: public Ui_w_screenshoterror {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_SCREENSHOTERROR_H
