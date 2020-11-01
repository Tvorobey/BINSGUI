#ifndef LABELWITHLINEEDIT_H
#define LABELWITHLINEEDIT_H

#include <QWidget>

#include "inputfornumber.h"

namespace Ui {
class LabelWithLineEdit;
}

class LabelWithLineEdit : public QWidget
{
    Q_OBJECT

public:
    explicit LabelWithLineEdit(const QString& labelName, QWidget *parent = 0);
    ~LabelWithLineEdit();

    double getValue() const;

    void enableInput();
    void disableInput();

    void setValue(const QString& value);

    void clear();

private:
    Ui::LabelWithLineEdit *ui;

};

#endif // LABELWITHLINEEDIT_H
