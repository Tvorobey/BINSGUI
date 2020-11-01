#ifndef ETHCONFIG_H
#define ETHCONFIG_H

#include <QObject>
#include <QUdpSocket>
#include <QJsonObject>
#include <QDebug>
#include <QThread>
#include <QMutex>

#include "./Utilities/lock.h"
#include "./CommonDefinition/definition.h"

using AppDefinition::controlBINS::OperateData;


class EthConfig : public QObject
{
    Q_OBJECT
public:
    explicit EthConfig(const QJsonObject &config, QObject *parent = nullptr);

    virtual ~EthConfig();

protected:

    QUdpSocket* m_Socket;

private:

    QUdpSocket *MakeSocket(const QJsonObject& config);


};

class ListenEthernet : public EthConfig
{
    Q_OBJECT
public:
    ListenEthernet(const QJsonObject &config);

public slots:

    void readData();

private:

    QByteArray m_baDatagram;

signals:

    void gotData(const QByteArray& data);

};

class WriteEthernet : public EthConfig
{
    Q_OBJECT
public:
    WriteEthernet(const QJsonObject &config);

private:

    QMutex m_mutex;

public slots:

    void sendData(const OperateData& data);
};


#endif // ETHCONFIG_H
