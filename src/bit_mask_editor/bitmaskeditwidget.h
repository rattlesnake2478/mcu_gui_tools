#ifndef BITMASKEDITOR_H
#define BITMASKEDITOR_H

#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include "mask.h"

// TODO: reworkin with direct drawing to give ability to make track of points
class BitMaskEditWidget : public QWidget
{
    Q_OBJECT
public:
    BitMaskEditWidget(QWidget *parent = nullptr);
    BitMaskEditWidget(Mask mask, QWidget *parent = nullptr);

public slots:
    void setMask(const Mask& mask);

private:
    QGridLayout* layout_ = nullptr;
    QVector<QWidget*> points_;
    void fillFromMask();
    Mask mask_;

signals:
    void maskChanged(const Mask&);
};

#endif // BITMASKEDITOR_H
