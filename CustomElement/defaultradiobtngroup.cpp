#include "defaultradiobtngroup.h"
#include "ui_defaultradiobtngroup.h"

DefaultRadioBtnGroup::DefaultRadioBtnGroup(const QPair<QString, QString> &btnText, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DefaultRadioBtnGroup),
    m_btnGroup(new QButtonGroup(parent))
{
    ui->setupUi(this);

    createBtnGroup();

    setBtnText(btnText);

    connect(m_btnGroup.data(), static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            [=](int id){ emit btnClicked(id); });
}

DefaultRadioBtnGroup::~DefaultRadioBtnGroup()
{
    delete ui;
}

void DefaultRadioBtnGroup::setCheckedBtn(size_t idx)
{
    m_btnGroup.data()->button(idx)->setChecked(true);
}

void DefaultRadioBtnGroup::setButtonsState(const QString &state)
{
    for (int i = 0; i < m_btnGroup.data()->buttons().length(); ++i)
        m_btnGroup.data()->button(i)->setDisabled(state == "enable" ? false : true);
}


void DefaultRadioBtnGroup::createBtnGroup()
{
    m_btnGroup.data()->setExclusive(true);
    m_btnGroup.data()->addButton(ui->leftRadioBtn, 0);
    m_btnGroup.data()->addButton(ui->rightRadioBtn, 1);
}

void DefaultRadioBtnGroup::setBtnText(const QPair<QString, QString> &btnText)
{
    ui->leftRadioBtn->setText(btnText.first);
    ui->rightRadioBtn->setText(btnText.second);
}
