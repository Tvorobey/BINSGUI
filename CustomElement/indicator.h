#ifndef INDICATOR_H
#define INDICATOR_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class Indicator;
}

class Indicator : public QWidget
{
    Q_OBJECT

public:
    explicit Indicator(QWidget *parent = 0);
    ~Indicator();

    void setState(bool isOn = false)
    {
        m_isOn = isOn;
        this->repaint();
    }


private:
    Ui::Indicator *ui;

    void paintEvent(QPaintEvent*);

    bool m_isOn;
};

#endif // INDICATOR_H
