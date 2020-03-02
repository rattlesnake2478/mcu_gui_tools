#include <QApplication>
#include <QLabel>
#include <QDebug>

#include "src/tools/maskeditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MaskEditor editor;
    editor.show();

    return a.exec();
}
