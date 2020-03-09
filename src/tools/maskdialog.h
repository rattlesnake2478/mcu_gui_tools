#ifndef MASKDIALOG_H
#define MASKDIALOG_H

#include <QDialog>
#include <QLineEdit>

class MaskDialog : public QDialog
{
    Q_OBJECT
public:
    MaskDialog(QWidget* parent);

    struct Form {
        QString name = "Mask";
        uint16_t width = 10;
        uint16_t height = 10;
    };

    const Form& getForm() const { return form_; };

private:
    Form form_;
    QLineEdit* name_;
    QLineEdit* width_;
    QLineEdit* height_;

};

#endif // MASKDIALOG_H
