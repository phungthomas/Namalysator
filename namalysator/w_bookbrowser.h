#ifndef W_BOOKBROWSER_H
#define W_BOOKBROWSER_H

#include <QtGui/QWidget>

namespace Ui {
    class w_bookbrowser;
}

class w_bookbrowser : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(w_bookbrowser)
public:
    explicit w_bookbrowser(QWidget *parent = 0);
    virtual ~w_bookbrowser();
private:
    Ui::w_bookbrowser *m_ui;
};

#endif