#include "infofrombinsui.h"
#include "ui_infofrombinsui.h"

namespace
{
    void nullHandler(const QVariant&)
    {
    }
}


InfoFromBINSUI::InfoFromBINSUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoFromBINSUI)

{
    ui->setupUi(this);

    fillList();

    configUI();

    m_handlers.insert(PHI, [this](const QVariant& v)
    {
        ui->latitudeValue->setText(QString::number(v.toDouble(), 'f'));
    });

    m_handlers.insert(LYAMBDA, [this](const QVariant& v)
    {
        ui->longitudeValue->setText(QString::number(v.toDouble(), 'f'));
    });
    m_handlers.insert(HEADING, [this](const QVariant& v)
    {
        ui->headValue->setText(QString::number(v.toDouble(), 'f', 2));
    });
    m_handlers.insert(PITCH, [this](const QVariant& v)
    {
        ui->pitchValue->setText(QString::number(v.toDouble(), 'f', 2));
    });
    m_handlers.insert(ROLL, [this](const QVariant& v)
    {
        ui->rollValue->setText(QString::number(v.toDouble(), 'f', 2));
    });
    m_handlers.insert(SPEEDNORTH, [this](const QVariant& v)
    {
        ui->northSpeedValue->setText(QString::number(v.toDouble(), 'f', 4));
    });
    m_handlers.insert(SPEEDEAST, [this](const QVariant& v)
    {
        ui->eastSpeedValue->setText(QString::number(v.toDouble(), 'f', 4));
    });
    m_handlers.insert(CONNWITHBINS, [this](const QVariant& v)
    {
        m_InfoBINS[0].data()->changeIndicatorState(v.toBool());
    });
    m_handlers.insert(INITCOORDINATE, [this](const QVariant& v)
    {
        m_InfoBINS[1].data()->changeIndicatorState(v.toBool());
    });
    m_handlers.insert(READYSTATUS, [this](const QVariant& v)
    {
        m_InfoBINS[2].data()->changeIndicatorState(v.toBool());
    });
    m_handlers.insert(BINSREGIM, [this](const QVariant& v)
    {
        ui->binsRgmValue->setText(v.toString());
    });
    m_handlers.insert(LAGDATASTATUS, [this](const QVariant& v)
    {
        m_DataStatus[0].data()->changeIndicatorState(v.toBool());
    });
    m_handlers.insert(SNSDATASTATUS, [this](const QVariant& v)
    {
        m_DataStatus[1].data()->changeIndicatorState(v.toBool());
    });
}

InfoFromBINSUI::~InfoFromBINSUI()
{
    delete ui;
}

void InfoFromBINSUI::fromMap(const QVariantMap &data)
{
    for (auto i = data.constBegin(), e = data.constEnd(); i != e; i++)
        m_handlers.value(i.key(), nullHandler)(i.value());
}


void InfoFromBINSUI::fillList()
{
    m_InfoBINS.append(QSharedPointer<LabelWithIndicator>
                      (new LabelWithIndicator("Связь с БИНС:")));
    m_InfoBINS.append(QSharedPointer<LabelWithIndicator>
                      (new LabelWithIndicator("Начальные координаты для выставки приняты:")));
    m_InfoBINS.append(QSharedPointer<LabelWithIndicator>
                      (new LabelWithIndicator("Готовность:")));

    m_DataStatus.append(QSharedPointer<LabelWithIndicator>
                      (new LabelWithIndicator("Лаг")));
    m_DataStatus.append(QSharedPointer<LabelWithIndicator>
                      (new LabelWithIndicator("Внешняя СНС")));
}

void InfoFromBINSUI::configUI()
{
    for (int i = 0; i < m_InfoBINS.size(); ++i)
        ui->layoutBINSState->insertWidget(i, m_InfoBINS.at(i).data());

    for (int i = 0; i < m_DataStatus.size(); ++i)
        ui->layoutDataStatus->insertWidget(i, m_DataStatus.at(i).data());

}

