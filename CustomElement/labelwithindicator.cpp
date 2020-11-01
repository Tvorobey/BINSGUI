#include "labelwithindicator.h"
#include "ui_labelwithindicator.h"

LabelWithIndicator::LabelWithIndicator(const QString &labelText, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LabelWithIndicator)
{
    ui->setupUi(this);

    ui->label->setText(labelText);
}

LabelWithIndicator::~LabelWithIndicator()
{
    delete ui;
}

void LabelWithIndicator::changeIndicatorState(bool isOn)
{
    ui->indicator->setState(isOn);
}
