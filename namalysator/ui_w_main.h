/********************************************************************************
** Form generated from reading UI file 'w_main.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_MAIN_H
#define UI_W_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_w_main
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *w_main)
    {
        if (w_main->objectName().isEmpty())
            w_main->setObjectName(QString::fromUtf8("w_main"));
        w_main->resize(800, 600);
        centralwidget = new QWidget(w_main);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        w_main->setCentralWidget(centralwidget);
        menubar = new QMenuBar(w_main);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 19));
        w_main->setMenuBar(menubar);
        statusbar = new QStatusBar(w_main);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        w_main->setStatusBar(statusbar);

        retranslateUi(w_main);

        QMetaObject::connectSlotsByName(w_main);
    } // setupUi

    void retranslateUi(QMainWindow *w_main)
    {
        w_main->setWindowTitle(QCoreApplication::translate("w_main", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class w_main: public Ui_w_main {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_MAIN_H
