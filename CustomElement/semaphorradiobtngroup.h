#ifndef SEMAPHORRADIOBTNGROUP_H
#define SEMAPHORRADIOBTNGROUP_H

#include <QWidget>
#include <QScopedPointer>
#include <QButtonGroup>

namespace Ui {
class SemaphorRadioBtnGroup;
}

class SemaphorRadioBtnGroup : public QWidget
{
    Q_OBJECT

public:
    explicit SemaphorRadioBtnGroup(const QString& labelName, QWidget *parent = 0);
    ~SemaphorRadioBtnGroup();

    void setState(bool isOn = true);

private:
    Ui::SemaphorRadioBtnGroup *ui;

    QScopedPointer<QButtonGroup>    m_btnGroup;

    void createBtnGroup();

signals:

    void btnClicked(size_t id);
};

#endif // SEMAPHORRADIOBTNGROUP_H
