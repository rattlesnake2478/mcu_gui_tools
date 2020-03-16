#include "bmpconverter.h"

#include <QImage>
#include <QFileDialog>
#include "src/bit_mask_editor/mask.h"


BmpConverter::BmpConverter(QWidget* parent)
    :QLabel(parent)
{
    QFileDialog dialog(this, "Open Mask file");
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Images (*.bmp)"));

    if (dialog.exec() == QDialog::Accepted) {
        QImage image;
        if (!image.load(dialog.selectedFiles().constFirst())) {
            setText("Cannot load image");
            return;
        }
        if (image.format() != QImage::Format_Mono) {
            setText("Wrong bmp format");
            return;
        }
        Mask mask(image.width(), image.height());
        for (int i = 0; i < image.height(); ++i)
            for (int j = 0; j < image.width(); ++j) {
                auto pixel = image.pixelColor(i, j);
                if (pixel.red() == 0) mask.setAt(i, j, true);
            }

        setTextInteractionFlags(Qt::TextSelectableByMouse);
        setText(mask.toString());

    }
}
