#ifndef HANDLERDATALAG_H
#define HANDLERDATALAG_H

#include <QObject>
#include <QScopedPointer>

#include "./ConnectionConfig/ethconfig.h"
#include "./GlobalStruct/exchangestruct.h"
#include "./CommonDefinition/definition.h"

using DriverExchange::DataFromLag;
using DriverExchange::FlagsFromLag;
using DriverExchange::ConnectionQuality;

using namespace AppDefinition::LAG;

class HandlerDataLag : public QObject
{
    Q_OBJECT
public:
    explicit HandlerDataLag(const QJsonObject& config, QObject *parent = nullptr);
private:

    QScopedPointer<ListenEthernet>  m_EthFromLag;

    QJsonObject m_config;

    DataFromLag m_data;

    QVariantMap m_map
    {
        { SPEED_VX,             0 },
        { SPEED_VZ,             0 },
        { SPEED_VY,             0 },
        { SPEED_VALID,          "Не валидна" },
        { HEIGHT_VALID,         "Не валидна" },
        { REVERBERATION_SOLID,  "НЕТ"},
        { PWM_ENABLE,           "Запрещено"}
    };

private:

    void fillMap();

signals:

    void dataReady(const QVariantMap&   data);

public slots:

    void fillDataStruct(const QByteArray& array);

    void initAndStart();

signals:

public slots:
};

#endif // HANDLERDATALAG_H
