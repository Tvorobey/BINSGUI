#ifndef CORRECTIONCONTROLUI_H
#define CORRECTIONCONTROLUI_H

#include <QWidget>
#include <QScopedPointer>

#include "semaphorradiobtngroup.h"
#include "defaultradiobtngroup.h"

namespace Ui {
class CorrectionControlUI;
}

class CorrectionControlUI : public QWidget
{
    Q_OBJECT

public:
    explicit CorrectionControlUI(QWidget *parent = 0);
    ~CorrectionControlUI();

private:
    Ui::CorrectionControlUI *ui;

    QScopedPointer<SemaphorRadioBtnGroup>   m_SNSControl;
    QScopedPointer<SemaphorRadioBtnGroup>   m_LagControl;

    QScopedPointer<DefaultRadioBtnGroup>    m_CorrectionPriority;

private:

    void configUI();

signals:

    void changeSpeedPriority(size_t idx);
};

#endif // CORRECTIONCONTROLUI_H
