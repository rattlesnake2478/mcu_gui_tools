#ifndef BITMASKEDITPOINT_H
#define BITMASKEDITPOINT_H

#include <QWidget>

class BitMaskEditPoint : public QWidget
{
    Q_OBJECT
public:
    explicit BitMaskEditPoint(bool state = false, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void toggled(bool state);

private:
    void setStatePalette();
    bool state_;
};

#endif // BITMASKEDITPOINT_H
