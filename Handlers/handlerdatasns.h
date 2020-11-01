#ifndef HANDLERDATASNS_H
#define HANDLERDATASNS_H

#include <QObject>
#include <QScopedPointer>

#include "./ConnectionConfig/ethconfig.h"
#include "./GlobalStruct/exchangestruct.h"
#include "./CommonDefinition/definition.h"

using DriverExchange::DataFromSNS;

using namespace AppDefinition::SNS;

class HandlerDataSNS : public QObject
{
    Q_OBJECT
public:
    explicit HandlerDataSNS(const QJsonObject& config, QObject *parent = nullptr);

private:

    QScopedPointer<ListenEthernet>  m_EthFromSNS;

    QJsonObject m_config;

    DataFromSNS m_data;

    QVariantMap m_map
    {
        { LATITUDE,     0 },
        { LONGITUDE,    0 },
        { ABS_SPEED,    0 },
        { NORTH_SPEED,  0 },
        { EAST_SPEED,   0 },
        { STATUS,       "DISCONNECT"}
    };

private:

    void fillMap();

signals:

    void dataReady(const QVariantMap&   data);

public slots:

    void fillDataStruct(const QByteArray& array);

    void initAndStart();
};

#endif // HANDLERDATASNS_H
