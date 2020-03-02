#include "bitmaskeditpoint.h"

#include <QMouseEvent>
#include <QDebug>

BitMaskEditPoint::BitMaskEditPoint(bool state, QWidget *parent)
    : QWidget(parent), state_(state)
{
    setStatePalette();
    setAutoFillBackground(true);

    setFixedSize(30, 30);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void
BitMaskEditPoint::mousePressEvent(QMouseEvent *) {
    state_ = !state_;
    setStatePalette();
    emit toggled(state_);
}

void
BitMaskEditPoint::setStatePalette() {
    QPalette pal(palette());
    QColor col = state_ ? QColorConstants::DarkBlue : QColorConstants::LightGray;
    pal.setColor(QPalette::Window, col);
    setPalette(pal);
}
