#include "semaphorradiobtngroup.h"
#include "ui_semaphorradiobtngroup.h"

SemaphorRadioBtnGroup::SemaphorRadioBtnGroup(const QString &labelName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SemaphorRadioBtnGroup),
    m_btnGroup(new QButtonGroup(parent))
{
    ui->setupUi(this);

    ui->label->setText(labelName);

    createBtnGroup();

    connect(m_btnGroup.data(), static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            [=](int id){ emit btnClicked(id); });
}

SemaphorRadioBtnGroup::~SemaphorRadioBtnGroup()
{
    delete ui;
}

void SemaphorRadioBtnGroup::setState(bool isOn)
{
    m_btnGroup.data()->button(isOn ? 0 : 1)->setChecked(true);
}

void SemaphorRadioBtnGroup::createBtnGroup()
{
    m_btnGroup.data()->setExclusive(true);
    m_btnGroup.data()->addButton(ui->btnOn, 0);
    m_btnGroup.data()->addButton(ui->btnOff, 1);
}
