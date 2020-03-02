#include "bitmaskeditwidget.h"
#include "bitmaskeditpoint.h"

BitMaskEditWidget::BitMaskEditWidget(QWidget* parent)
    :BitMaskEditWidget(Mask(), parent)
{
}

BitMaskEditWidget::BitMaskEditWidget(Mask mask, QWidget *parent)
    : QWidget(parent), mask_(mask)
{
    fillFromMask();
}

void
BitMaskEditWidget::setMask(const Mask& mask) {
    mask_ = mask;
    fillFromMask();
}

void
BitMaskEditWidget::fillFromMask() {
    if (layout_ != nullptr) {
        delete layout_;
        points_.clear();
        points_.reserve(mask_.getWidth() * mask_.getHeight());
    }
    layout_ = new QGridLayout(this);

    for(int i = 0; i < mask_.getWidth(); ++i) {
        for(int j = 0; j < mask_.getHeight(); ++j) {
            auto point = new BitMaskEditPoint(mask_.getAt(j, i), this);
            layout_->addWidget(point, i, j);
            connect(point, &BitMaskEditPoint::toggled, [this, i, j](bool state){
                this->mask_.setAt(j, i, state);
                emit maskChanged(this->mask_);
            });
            points_.push_back(point);
        }
    }
}
