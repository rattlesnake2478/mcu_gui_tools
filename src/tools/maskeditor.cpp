#include "maskeditor.h"

#include <QMenuBar>
#include <QAction>
#include <QIcon>
#include <QGridLayout>
#include <QScrollArea>
#include <QListView>
#include <QFileDialog>

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
        storage_->loadFromFile(dialog.selectedFiles().constFirst());
        auto selection_model = mask_list_->selectionModel();
        selection_model->setCurrentIndex(storage_->index(0), QItemSelectionModel::SelectCurrent);
    }
}

void
MaskEditor::saveMaskFile() {
    QFileDialog dialog(this, tr("Save Mask file"));
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    if (dialog.exec() == QDialog::Accepted) {
        storage_->saveToFile(dialog.selectedFiles().constFirst());
    }
}

void
MaskEditor::setupMenu() {
    auto fileMenu = menuBar()->addMenu(tr("&File"));

    // Menu
    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/icons/open-icon"));
    QAction *openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an mask file"));
    connect(openAct, &QAction::triggered, this, &MaskEditor::openMaskFile);
    fileMenu->addAction(openAct);

    const QIcon saveIcon = QIcon::fromTheme("document-save-as", QIcon(":/icons/save-icon"));
    QAction *saveAct = new QAction(saveIcon, tr("&Save..."), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save mask file"));
    connect(saveAct, &QAction::triggered, this, &MaskEditor::saveMaskFile);
    fileMenu->addAction(saveAct);

    const QIcon exitIcon = QIcon::fromTheme("application-exit", QIcon(":/icons/exit-icon"));
    QAction *exitAct = new QAction(exitIcon, tr("&Quit..."), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the mask editor"));
    connect(exitAct, &QAction::triggered, this, &MaskEditor::close);
    fileMenu->addAction(exitAct);
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
