#ifndef BMPCONVERTER_H
#define BMPCONVERTER_H

#include <QLabel>

class BmpConverter : public QLabel
{
    Q_OBJECT
public:
    BmpConverter(QWidget* parent = nullptr);
};

#endif // BMPCONVERTER_H
