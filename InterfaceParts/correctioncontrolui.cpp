#include "correctioncontrolui.h"
#include "ui_correctioncontrolui.h"

CorrectionControlUI::CorrectionControlUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorrectionControlUI),
    m_SNSControl(new SemaphorRadioBtnGroup("СНС:")),
    m_LagControl(new SemaphorRadioBtnGroup("Лаг:")),
    m_CorrectionPriority(new DefaultRadioBtnGroup(QPair<QString,QString>("СНС","Лаг")))
{
    ui->setupUi(this);

    configUI();

    connect(m_CorrectionPriority.data(), &DefaultRadioBtnGroup::btnClicked, this,
            [this](size_t id)
    {
        emit changeSpeedPriority(id);
    });
}

CorrectionControlUI::~CorrectionControlUI()
{
    delete ui;
}

void CorrectionControlUI::configUI()
{
    ui->layoutGroupBox->insertWidget(0, m_SNSControl.data());
    ui->layoutGroupBox->insertWidget(1, m_LagControl.data());
    ui->layoutGroupBox->insertWidget(4, m_CorrectionPriority.data());

    m_SNSControl.data()->setState(false);
    m_LagControl.data()->setState(false);

    m_CorrectionPriority.data()->setCheckedBtn(1);
}
