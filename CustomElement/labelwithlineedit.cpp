#include "labelwithlineedit.h"
#include "ui_labelwithlineedit.h"

LabelWithLineEdit::LabelWithLineEdit(const QString &labelName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LabelWithLineEdit)
{
    ui->setupUi(this);

    ui->label->setText(labelName);

}

LabelWithLineEdit::~LabelWithLineEdit()
{
    delete ui;
}

double LabelWithLineEdit::getValue() const
{
    return ui->input->getInputValue();
}

void LabelWithLineEdit::enableInput()
{
    ui->input->setEnabled(true);
}

void LabelWithLineEdit::disableInput()
{
    ui->input->setDisabled(true);
}

void LabelWithLineEdit::setValue(const QString &value)
{
    ui->input->setText(value);
}

void LabelWithLineEdit::clear()
{
    ui->input->clear();
}

