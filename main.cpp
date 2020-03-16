#include <QApplication>

#include "src/tools/bmpconverter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BmpConverter converter;
    converter.show();


    return a.exec();
}
