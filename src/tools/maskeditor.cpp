#include "maskeditor.h"

#include <QMenuBar>
#include <QAction>
#include <QIcon>
#include <QGridLayout>
#include <QScrollArea>
#include <QListView>
#include <QFileDialog>
#include <QMessageBox>

#include "bitmaskstorage.h"

MaskEditor::MaskEditor(QWidget *parent) : QMainWindow(parent)
{
    setupMenu();
    setupLayout();
    setupLayoutInteraction();
}

void
MaskEditor::openMaskFile() {
    QFileDialog dialog(this, tr("Open Mask file"));
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    if (dialog.exec() == QDialog::Accepted) {
        auto result = storage_->loadFromFile(dialog.selectedFiles().constFirst());
        if (result.length() != 0) {
            QMessageBox::warning(this, "Cannot open masks", result);
        } else {
            auto selection_model = mask_list_->selectionModel();
            selection_model->setCurrentIndex(storage_->index(0), QItemSelectionModel::SelectCurrent);
        }
    }
}

void
MaskEditor::saveMaskFile() {
    QFileDialog dialog(this, tr("Save Mask file"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() == QDialog::Accepted) {
        auto result = storage_->saveToFile(dialog.selectedFiles().constFirst());
        if (result.length() != 0) {
            QMessageBox::warning(this, "Cannot save masks", result);
        }
    }
}

void
MaskEditor::setupMenu() {
    auto fileMenu = menuBar()->addMenu(tr("&File"));

    // Menu
    QAction *openAction = fileMenu->addAction(tr("&Open..."), this, &MaskEditor::openMaskFile);
    openAction->setShortcuts(QKeySequence::Open);

    QAction *saveAction = fileMenu->addAction(tr("&Save..."), this, &MaskEditor::saveMaskFile);
    saveAction->setShortcuts(QKeySequence::Save);

    QAction *exitAction = fileMenu->addAction(tr("&Quit..."), this, &MaskEditor::close);
    exitAction->setShortcut(QKeySequence::Quit);
}
void
MaskEditor::setupLayout() {
    //Widget data
    QGridLayout* main_layout = new QGridLayout();
    mask_data_ = new QLabel();
    mask_data_->setTextInteractionFlags(Qt::TextSelectableByMouse);
    main_layout->addWidget(mask_data_, 1, 1, 1, 5);

    viewer_ = new BitMaskViewer(BitMaskViewer::DEFAULT_SCALE, this);
    main_layout->addWidget(viewer_, 2, 5);

    editor_ = new BitMaskEditWidget(this);
    QScrollArea* area = new QScrollArea(this);
    area->setMinimumSize({375, 375});
    area->setWidget(editor_);
    main_layout->addWidget(area, 2, 1, 4, 4);

    mask_list_ = new QListView();
    mask_list_->setViewMode(QListView::ListMode);
    main_layout->addWidget(mask_list_, 3,5);

    QWidget* main = new QWidget(this);
    main->setLayout(main_layout);
    setCentralWidget(main);
}

void
MaskEditor::setupLayoutInteraction() {
    storage_ = new BitMaskStorage(this);
    mask_list_->setModel(storage_);

    auto selection_model = mask_list_->selectionModel();
    connect(selection_model, &QItemSelectionModel::currentChanged, [this](const QModelIndex &current) {
        auto mask = current.data(BitMaskStorage::MaskViewRole).value<Mask>();
        this->viewer_->showMask(mask);
        this->editor_->setMask(mask);
        this->mask_data_->setText(mask.toString());
    });
    selection_model->setCurrentIndex(storage_->index(0), QItemSelectionModel::SelectCurrent);

    connect(editor_, &BitMaskEditWidget::maskChanged, viewer_, &BitMaskViewer::showMask);
    connect(editor_, &BitMaskEditWidget::maskChanged, [this](const Mask& mask){
       this->mask_data_->setText(mask.toString());
       auto index = this->mask_list_->selectionModel()->currentIndex();
       auto data = QVariant();
       data.setValue(mask);
       this->storage_->setData(index, data, BitMaskStorage::MaskEditRole);
    });
}
