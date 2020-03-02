#ifndef BITMASKVIEWER_H
#define BITMASKVIEWER_H

#include <QWidget>
#include <QPixmap>
#include "mask.h"

class BitMaskViewer : public QWidget
{
    Q_OBJECT
public:
    static const uint8_t DEFAULT_SCALE = 4;
    BitMaskViewer(uint8_t scale = DEFAULT_SCALE, QWidget *parent = nullptr);
    virtual QSize sizeHint() const override;

public slots:
    void showMask(const Mask& mask);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    uint8_t scale_;
    QPixmap* main_image_;
};

#endif // BITMASKVIEWER_H
