#include "inputfornumber.h"

InputForNumber::InputForNumber(QWidget *parent) : QLineEdit(parent),
    valueRange("[+]?[0-9]*[.][0-9]+(?:[eE][+]?[0-9]+)?"),
    valueRegex("^" + valueRange + "$"),
    valueValidator(new QRegExpValidator(valueRegex, this))
{
    this->setValidator(valueValidator);
}

InputForNumber::InputForNumber(const QString &text, QWidget *parent) :
    QLineEdit(text, parent),
    valueRange("[+]?[0-9]*[.][0-9]+(?:[eE][+]?[0-9]+)?"),
    valueRegex("^" + valueRange + "\\." + valueRange + "$"),
    valueValidator(new QRegExpValidator(valueRegex, this))
{
    this->setValidator(valueValidator);
}

double InputForNumber::getInputValue()
{
    return this->text().toDouble();
}
