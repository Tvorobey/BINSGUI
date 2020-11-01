#ifndef LABELWITHINDICATOR_H
#define LABELWITHINDICATOR_H

#include <QWidget>

namespace Ui {
class LabelWithIndicator;
}

class LabelWithIndicator : public QWidget
{
    Q_OBJECT

public:
    explicit LabelWithIndicator(const QString& labelText, QWidget *parent = 0);
    ~LabelWithIndicator();

    void changeIndicatorState(bool isOn = false);

private:
    Ui::LabelWithIndicator *ui;
};

#endif // LABELWITHINDICATOR_H
