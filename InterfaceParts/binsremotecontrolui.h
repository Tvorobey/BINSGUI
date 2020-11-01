#ifndef BINSREMOTECONTROLUI_H
#define BINSREMOTECONTROLUI_H

#include <QWidget>
#include <QScopedPointer>

#include "semaphorradiobtngroup.h"

namespace Ui {
class BINSRemoteControlUI;
}

class BINSRemoteControlUI : public QWidget
{
    Q_OBJECT

public:
    explicit BINSRemoteControlUI(QWidget *parent = 0);
    ~BINSRemoteControlUI();

private:
    Ui::BINSRemoteControlUI *ui;

    QScopedPointer<SemaphorRadioBtnGroup>   m_PultControl;
    QScopedPointer<SemaphorRadioBtnGroup>   m_BortControl;

private:

    void configUI();

};

#endif // BINSREMOTECONTROLUI_H
