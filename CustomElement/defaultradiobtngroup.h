#ifndef DEFAULTRADIOBTNGROUP_H
#define DEFAULTRADIOBTNGROUP_H

#include <QWidget>
#include <QDebug>
#include <QPair>
#include <QScopedPointer>
#include <QButtonGroup>

namespace Ui {
class DefaultRadioBtnGroup;
}

class DefaultRadioBtnGroup : public QWidget
{
    Q_OBJECT

public:
    explicit DefaultRadioBtnGroup(const QPair<QString,QString>& btnText,
                                  QWidget *parent = 0);
    ~DefaultRadioBtnGroup();

    void setCheckedBtn(size_t idx);
    void setButtonsState(const QString& state = "enable");

private:
    Ui::DefaultRadioBtnGroup *ui;

    QScopedPointer<QButtonGroup>    m_btnGroup;

    void createBtnGroup();
    void setBtnText(const QPair<QString,QString>& btnText);

signals:

    void btnClicked(size_t id);
};

#endif // DEFAULTRADIOBTNGROUP_H
