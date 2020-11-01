#include "binsremotecontrolui.h"
#include "ui_binsremotecontrolui.h"

BINSRemoteControlUI::BINSRemoteControlUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BINSRemoteControlUI),
    m_PultControl(new SemaphorRadioBtnGroup("Пульт:")),
    m_BortControl(new SemaphorRadioBtnGroup("Борт:"))
{
    ui->setupUi(this);

    configUI();

    connect(m_PultControl.data(), &SemaphorRadioBtnGroup::btnClicked, this,
            [this](size_t id)
    {
        m_BortControl.data()->setState((id == 1) ? true : false );
    });

    connect(m_BortControl.data(), &SemaphorRadioBtnGroup::btnClicked, this,
            [this](size_t id)
    {
        m_PultControl.data()->setState((id == 1) ? true : false );
    });
}

BINSRemoteControlUI::~BINSRemoteControlUI()
{
    delete ui;
}

void BINSRemoteControlUI::configUI()
{
    ui->layoutGroupBox->insertWidget(0, m_PultControl.data());
    ui->layoutGroupBox->insertWidget(1, m_BortControl.data());

    m_PultControl.data()->setState();
    m_BortControl.data()->setState(false);
}
