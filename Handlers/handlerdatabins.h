#ifndef HANDLERDATABINS_H
#define HANDLERDATABINS_H

#include <QObject>
#include <QScopedPointer>
#include <QMap>
#include <bitset>
#include <QMessageBox>

#include <./ConnectionConfig/ethconfig.h>
#include "./GlobalStruct/exchangestruct.h"
#include "./CommonDefinition/definition.h"

using namespace AppDefinition::BINS;

using namespace DriverExchange;

class HandlerDataBINS : public QObject
{
    Q_OBJECT
public:
    explicit HandlerDataBINS(const QJsonObject &config, QObject *parent = nullptr);

private:

    QScopedPointer<ListenEthernet> m_EthFromBINS;

    QJsonObject m_config;

    DataFromBINS    m_DataBINS;

    std::bitset<16> m_ComBitCheck,
                    m_EthBitCheck;

    QVariantMap m_map
    {
        { PHI,              0 },
        { LYAMBDA,          0 },
        { HEADING,          0 },
        { PITCH,            0 },
        { ROLL,             0 },
        { SPEEDNORTH,       0 },
        { SPEEDEAST,        0 },
        { CONNWITHBINS,     false },
        { INITCOORDINATE,   false },
        { READYSTATUS,      false},
        { BINSREGIM,        "Автономный" },
        { LAGDATASTATUS,    false},
        { SNSDATASTATUS,    false},
        { COMCONNECTSTATUS, false}
    };

private:

    void decryptStatusWord(int ComStatusWord, unsigned short EthStatusWord );

    void fillMap();

signals:

    void dataReady(const QMap<QString, QVariant>& inputData);

public slots:

    void workWithData(const QByteArray& array);

    void initAndStart();
};

#endif // HANDLERDATABINS_H
