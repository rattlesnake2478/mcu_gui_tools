#include "bitmaskviewer.h"

#include <QPainter>
#include <QColor>
#include <QSizePolicy>

BitMaskViewer::BitMaskViewer(uint8_t scale, QWidget *parent)
    :QWidget(parent), scale_(scale)
{
    main_image_ = new QPixmap(Mask::DEFAULT_SIZE * scale_, Mask::DEFAULT_SIZE * scale_);
    main_image_->fill(QColorConstants::White);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

QSize
BitMaskViewer::
sizeHint() const {
    return {main_image_->width(), main_image_->height()};
}

void
BitMaskViewer::showMask(const Mask& mask) {
    if (main_image_->width() != mask.getWidth() * scale_
            || main_image_->height() != mask.getHeight() * scale_) {
        delete main_image_;
        main_image_ = new QPixmap(mask.getWidth() * scale_, mask.getHeight() * scale_);
    }
    main_image_->fill(QColorConstants::White);

    QPainter painter(main_image_);
    painter.setPen(QPen(QColorConstants::Black, scale_));
    for (int i = 0; i < mask.getWidth(); ++i) {
        for(int j = 0; j < mask.getHeight(); ++j) {
            if (mask.getAt(i, j)) {
                painter.drawPoint(i * scale_ + scale_ / 2, j * scale_ + scale_ / 2);
            }
        }
    }
    repaint();
}

void
BitMaskViewer::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0,0, *main_image_);
}
