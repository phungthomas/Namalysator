#include "w_bookbrowser.h"
#include "ui_w_bookbrowser.h"

w_bookbrowser::w_bookbrowser(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::w_bookbrowser)
{
    m_ui->setupUi(this);
}

w_bookbrowser::~w_bookbrowser()
{
    delete m_ui;
}