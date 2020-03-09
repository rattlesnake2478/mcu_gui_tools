#include "maskdialog.h"

#include <QFormLayout>
#include <QDialogButtonBox>

MaskDialog::MaskDialog(QWidget* parent)
    :QDialog(parent)
{
    name_ = new QLineEdit(this);
    name_->setText(form_.name);
    connect(name_, &QLineEdit::textChanged, [this](const QString text) {
       this->form_.name = text;
    });

    width_ = new QLineEdit(this);
    width_->setInputMask("09");
    width_->setText(QString::number(form_.width));
    connect(width_, &QLineEdit::textChanged, [this](const QString text) {
       this->form_.width = text.toUInt();
    });

    height_ = new QLineEdit(this);
    height_->setInputMask("09");
    height_->setText(QString::number(form_.height));
    connect(width_, &QLineEdit::textChanged, [this](const QString text) {
       this->form_.height = text.toUInt();
    });

    auto layout = new QFormLayout();
    layout->addRow("Name", name_);
    layout->addRow("Width", width_);
    layout->addRow("Height", height_);

    auto buttonBox = new QDialogButtonBox(this);
    buttonBox->addButton("Save", QDialogButtonBox::AcceptRole);
    buttonBox->addButton("Cancel", QDialogButtonBox::RejectRole);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &MaskDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &MaskDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(layout);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

}
