#include "w_bookbrowser.h"
#include "ui_w_bookbrowser.h"
#include <sstream>
 #include <QString>

w_bookbrowser::w_bookbrowser(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::w_bookbrowser)
{
    m_ui->setupUi(this);
	connect (m_ui->currentPage, SIGNAL(valueChanged(int)),this, SLOT(currentPage(int) ));
}

w_bookbrowser::~w_bookbrowser()
{
    delete m_ui;
}

void w_bookbrowser::currentPage(int nbPage){
	
	std::ostringstream oss;
	oss << nbPage;
	QString value = oss.str().c_str();
	m_ui ->titleValue->setText(value);
}
