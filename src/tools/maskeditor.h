#ifndef MASKEDITOR_H
#define MASKEDITOR_H

#include <QMainWindow>
#include <QLabel>
#include <QListView>

#include "src/bit_mask_editor/bitmaskeditwidget.h"
#include "src/bit_mask_editor/bitmaskviewer.h"
#include "src/bit_mask_editor/bitmaskstorage.h"

class MaskEditor : public QMainWindow
{
    Q_OBJECT
public:
    explicit MaskEditor(QWidget *parent = nullptr);

private:
    void setupMenu();
    void setupLayout();
    void setupLayoutInteraction();
    BitMaskEditWidget* editor_;
    QLabel* mask_data_;
    BitMaskViewer* viewer_;
    BitMaskStorage* storage_;
    QListView* mask_list_;
};

#endif // MASKEDITOR_H
