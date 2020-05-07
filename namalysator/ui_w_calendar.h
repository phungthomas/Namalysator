/********************************************************************************
** Form generated from reading UI file 'w_calendar.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_W_CALENDAR_H
#define UI_W_CALENDAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_w_calendar
{
public:
    QCalendarWidget *calendarDec;
    QLabel *lblHeader;
    QCalendarWidget *calendarAug;
    QCalendarWidget *calendarJul;
    QCalendarWidget *calendarJan;
    QCalendarWidget *calendarFev;
    QCalendarWidget *calendarJun;
    QCalendarWidget *calendarMai;
    QScrollArea *scrollAreaHeader;
    QWidget *scrollAreaWidgetContents;
    QCalendarWidget *calendarSep;
    QCalendarWidget *calendarMar;
    QCalendarWidget *calendarOct;
    QCalendarWidget *calendarApr;
    QCalendarWidget *calendarNov;
    QGroupBox *groupBox_4;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *lbFileName;
    QLabel *lbIssueNumber;
    QLabel *lbIssueParsed;
    QLabel *lbPages;
    QListWidget *listSupplement;
    QListWidget *listMets;
    QComboBox *cbYear;
    QLabel *label;
    QGroupBox *groupBoxComment;
    QLabel *label_2;
    QPushButton *btnAddComment;
    QPushButton *btnCancel;
    QTextEdit *txtComment;
    QLineEdit *dateComment;
    QPushButton *btnViewMets;
    QListWidget *listWidget;

    void setupUi(QWidget *w_calendar)
    {
        if (w_calendar->objectName().isEmpty())
            w_calendar->setObjectName(QString::fromUtf8("w_calendar"));
        w_calendar->resize(1014, 969);
        w_calendar->setFocusPolicy(Qt::ClickFocus);
        w_calendar->setAutoFillBackground(true);
        calendarDec = new QCalendarWidget(w_calendar);
        calendarDec->setObjectName(QString::fromUtf8("calendarDec"));
        calendarDec->setGeometry(QRect(760, 720, 240, 148));
        lblHeader = new QLabel(w_calendar);
        lblHeader->setObjectName(QString::fromUtf8("lblHeader"));
        lblHeader->setGeometry(QRect(262, 162, 211, 21));
        calendarAug = new QCalendarWidget(w_calendar);
        calendarAug->setObjectName(QString::fromUtf8("calendarAug"));
        calendarAug->setGeometry(QRect(760, 560, 240, 148));
        calendarJul = new QCalendarWidget(w_calendar);
        calendarJul->setObjectName(QString::fromUtf8("calendarJul"));
        calendarJul->setGeometry(QRect(510, 560, 240, 148));
        calendarJan = new QCalendarWidget(w_calendar);
        calendarJan->setObjectName(QString::fromUtf8("calendarJan"));
        calendarJan->setGeometry(QRect(10, 400, 240, 148));
        calendarJan->setCursor(QCursor(Qt::ArrowCursor));
        calendarJan->setFocusPolicy(Qt::StrongFocus);
        calendarJan->setAutoFillBackground(true);
        calendarJan->setSelectionMode(QCalendarWidget::SingleSelection);
        calendarJan->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
        calendarFev = new QCalendarWidget(w_calendar);
        calendarFev->setObjectName(QString::fromUtf8("calendarFev"));
        calendarFev->setGeometry(QRect(260, 400, 240, 148));
        calendarFev->setFocusPolicy(Qt::StrongFocus);
        calendarFev->setGridVisible(false);
        calendarJun = new QCalendarWidget(w_calendar);
        calendarJun->setObjectName(QString::fromUtf8("calendarJun"));
        calendarJun->setGeometry(QRect(260, 560, 240, 148));
        calendarJun->setFocusPolicy(Qt::StrongFocus);
        calendarJun->setContextMenuPolicy(Qt::DefaultContextMenu);
        calendarJun->setAutoFillBackground(true);
        calendarJun->setSelectionMode(QCalendarWidget::SingleSelection);
        calendarJun->setNavigationBarVisible(true);
        calendarJun->setDateEditEnabled(true);
        calendarMai = new QCalendarWidget(w_calendar);
        calendarMai->setObjectName(QString::fromUtf8("calendarMai"));
        calendarMai->setGeometry(QRect(10, 560, 240, 148));
        scrollAreaHeader = new QScrollArea(w_calendar);
        scrollAreaHeader->setObjectName(QString::fromUtf8("scrollAreaHeader"));
        scrollAreaHeader->setGeometry(QRect(260, 10, 741, 331));
        scrollAreaHeader->setBaseSize(QSize(1000, 200));
        scrollAreaHeader->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 739, 329));
        scrollAreaHeader->setWidget(scrollAreaWidgetContents);
        calendarSep = new QCalendarWidget(w_calendar);
        calendarSep->setObjectName(QString::fromUtf8("calendarSep"));
        calendarSep->setGeometry(QRect(10, 720, 240, 148));
        calendarMar = new QCalendarWidget(w_calendar);
        calendarMar->setObjectName(QString::fromUtf8("calendarMar"));
        calendarMar->setGeometry(QRect(510, 400, 240, 148));
        calendarOct = new QCalendarWidget(w_calendar);
        calendarOct->setObjectName(QString::fromUtf8("calendarOct"));
        calendarOct->setGeometry(QRect(260, 720, 240, 148));
        calendarApr = new QCalendarWidget(w_calendar);
        calendarApr->setObjectName(QString::fromUtf8("calendarApr"));
        calendarApr->setGeometry(QRect(760, 400, 240, 148));
        calendarNov = new QCalendarWidget(w_calendar);
        calendarNov->setObjectName(QString::fromUtf8("calendarNov"));
        calendarNov->setGeometry(QRect(510, 720, 240, 148));
        groupBox_4 = new QGroupBox(w_calendar);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 10, 241, 291));
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 20, 61, 16));
        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 60, 111, 16));
        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 100, 131, 16));
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 134, 46, 20));
        label_15 = new QLabel(groupBox_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 180, 91, 16));
        lbFileName = new QLabel(groupBox_4);
        lbFileName->setObjectName(QString::fromUtf8("lbFileName"));
        lbFileName->setGeometry(QRect(10, 40, 171, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lbFileName->setFont(font);
        lbIssueNumber = new QLabel(groupBox_4);
        lbIssueNumber->setObjectName(QString::fromUtf8("lbIssueNumber"));
        lbIssueNumber->setGeometry(QRect(10, 80, 171, 16));
        lbIssueNumber->setFont(font);
        lbIssueParsed = new QLabel(groupBox_4);
        lbIssueParsed->setObjectName(QString::fromUtf8("lbIssueParsed"));
        lbIssueParsed->setGeometry(QRect(10, 120, 181, 16));
        lbIssueParsed->setFont(font);
        lbPages = new QLabel(groupBox_4);
        lbPages->setObjectName(QString::fromUtf8("lbPages"));
        lbPages->setGeometry(QRect(10, 160, 181, 16));
        lbPages->setFont(font);
        listSupplement = new QListWidget(groupBox_4);
        listSupplement->setObjectName(QString::fromUtf8("listSupplement"));
        listSupplement->setGeometry(QRect(5, 201, 231, 81));
        listMets = new QListWidget(w_calendar);
        listMets->setObjectName(QString::fromUtf8("listMets"));
        listMets->setGeometry(QRect(10, 310, 241, 81));
        cbYear = new QComboBox(w_calendar);
        cbYear->setObjectName(QString::fromUtf8("cbYear"));
        cbYear->setGeometry(QRect(340, 360, 121, 22));
        label = new QLabel(w_calendar);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 360, 71, 16));
        groupBoxComment = new QGroupBox(w_calendar);
        groupBoxComment->setObjectName(QString::fromUtf8("groupBoxComment"));
        groupBoxComment->setGeometry(QRect(10, 880, 671, 81));
        label_2 = new QLabel(groupBoxComment);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 20, 101, 16));
        btnAddComment = new QPushButton(groupBoxComment);
        btnAddComment->setObjectName(QString::fromUtf8("btnAddComment"));
        btnAddComment->setGeometry(QRect(440, 30, 75, 24));
        btnCancel = new QPushButton(groupBoxComment);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(540, 30, 75, 24));
        txtComment = new QTextEdit(groupBoxComment);
        txtComment->setObjectName(QString::fromUtf8("txtComment"));
        txtComment->setGeometry(QRect(130, 10, 301, 64));
        dateComment = new QLineEdit(groupBoxComment);
        dateComment->setObjectName(QString::fromUtf8("dateComment"));
        dateComment->setEnabled(false);
        dateComment->setGeometry(QRect(10, 40, 113, 20));
        btnViewMets = new QPushButton(w_calendar);
        btnViewMets->setObjectName(QString::fromUtf8("btnViewMets"));
        btnViewMets->setGeometry(QRect(880, 360, 121, 24));
        listWidget = new QListWidget(w_calendar);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(700, 890, 301, 71));

        retranslateUi(w_calendar);

        QMetaObject::connectSlotsByName(w_calendar);
    } // setupUi

    void retranslateUi(QWidget *w_calendar)
    {
        w_calendar->setWindowTitle(QCoreApplication::translate("w_calendar", "Form", nullptr));
        lblHeader->setText(QString());
#if QT_CONFIG(tooltip)
        calendarJun->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        groupBox_4->setTitle(QCoreApplication::translate("w_calendar", "Details of Mets", nullptr));
        label_11->setText(QCoreApplication::translate("w_calendar", "Filename :", nullptr));
        label_12->setText(QCoreApplication::translate("w_calendar", "Issue number as text:", nullptr));
        label_13->setText(QCoreApplication::translate("w_calendar", "Issue number as parsed :", nullptr));
        label_14->setText(QCoreApplication::translate("w_calendar", "Pages :", nullptr));
        label_15->setText(QCoreApplication::translate("w_calendar", "Supplements :", nullptr));
        lbFileName->setText(QCoreApplication::translate("w_calendar", "No issue selected", nullptr));
        lbIssueNumber->setText(QCoreApplication::translate("w_calendar", "No issue selected", nullptr));
        lbIssueParsed->setText(QCoreApplication::translate("w_calendar", "No issue selected", nullptr));
        lbPages->setText(QCoreApplication::translate("w_calendar", "No issue selected", nullptr));
        label->setText(QCoreApplication::translate("w_calendar", "Select year :", nullptr));
        groupBoxComment->setTitle(QCoreApplication::translate("w_calendar", "Add Comment", nullptr));
        label_2->setText(QCoreApplication::translate("w_calendar", "Remarks on date :", nullptr));
        btnAddComment->setText(QCoreApplication::translate("w_calendar", "Validate", nullptr));
        btnCancel->setText(QCoreApplication::translate("w_calendar", "Cancel", nullptr));
        btnViewMets->setText(QCoreApplication::translate("w_calendar", "Open Directory", nullptr));
    } // retranslateUi

};

namespace Ui {
    class w_calendar: public Ui_w_calendar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_W_CALENDAR_H
