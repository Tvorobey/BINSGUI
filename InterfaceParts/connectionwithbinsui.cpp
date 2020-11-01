#include "connectionwithbinsui.h"
#include "ui_connectionwithbinsui.h"


namespace
{
    void nullHandler(const QVariant&)
    {
    }
}

ConnectionWithBINSUI::ConnectionWithBINSUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionWithBINSUI)
{
    ui->setupUi(this);

    fillList();

    configUI();

    m_handlers.insert(CONNWITHBINS, [this](const QVariant& v)
    {
       m_ConnectionState[2].data()->changeIndicatorState(v.toBool());
    });
    m_handlers.insert(COMCONNECTSTATUS, [this](const QVariant& v)
    {
       m_ConnectionState[1].data()->changeIndicatorState(v.toBool());
    });
}

ConnectionWithBINSUI::~ConnectionWithBINSUI()
{
    delete ui;
}

void ConnectionWithBINSUI::fromMap(const QVariantMap &data)
{
    for (auto i = data.constBegin(), e = data.constEnd(); i != e; i++)
        m_handlers.value(i.key(), nullHandler)(i.value());
}

void ConnectionWithBINSUI::fillList()
{
    m_ConnectionState.append(QSharedPointer<LabelWithIndicator>
                             (new LabelWithIndicator("Внутренняя связь:")));
    m_ConnectionState.append(QSharedPointer<LabelWithIndicator>
                             (new LabelWithIndicator("RS-422:")));
    m_ConnectionState.append(QSharedPointer<LabelWithIndicator>
                             (new LabelWithIndicator("Ethernet:")));
}

void ConnectionWithBINSUI::configUI()
{
    for (int i = 0; i < m_ConnectionState.size(); ++i)
        ui->layoutGroupBox->insertWidget(i, m_ConnectionState.at(i).data());
}
