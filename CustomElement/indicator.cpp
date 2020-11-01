#include "indicator.h"
#include "ui_indicator.h"

Indicator::Indicator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Indicator),
    m_isOn(false)
{
    ui->setupUi(this);
}

Indicator::~Indicator()
{
    delete ui;
}


void Indicator::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setBrush(QBrush(m_isOn ? Qt::green : Qt::red));

    painter.drawRect(QRect(0, 0, 30, 30));
}
