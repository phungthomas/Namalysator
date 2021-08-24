#include "clickableLabel.h"

#include <QMouseEvent>

clickableLabel::clickableLabel(const QString& text, QWidget* parent)
    : QLabel(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(slotClicked()));
    connect(this, SIGNAL(rightClicked()), this, SLOT(slotRightClicked()));

}

void clickableLabel::slotClicked()
{
}
void clickableLabel::slotRightClicked()
{
}

void clickableLabel::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton) {
        emit rightClicked();

    }
    else {
        emit clicked();

    }
}


