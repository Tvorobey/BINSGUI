#ifndef INPUTFORNUMBER_H
#define INPUTFORNUMBER_H

#include <QLineEdit>
#include <QString>
#include <QRegExp>
#include <QRegularExpressionValidator>
#include <QList>
#include <QDebug>

class InputForNumber : public QLineEdit
{
public:
    explicit InputForNumber(QWidget *parent = Q_NULLPTR);
    explicit InputForNumber(const QString &text, QWidget *parent = Q_NULLPTR);

    double getInputValue();

private:

    QString valueRange;        // Строка для регулярного выражения

    QRegExp valueRegex;        // Регулярное выражение

    QRegExpValidator  *valueValidator;     // Валидатор, на проверку введенного



};

#endif // INPUTFORNUMBER_H
