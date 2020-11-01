#include "ethconfig.h"

EthConfig::EthConfig(const QJsonObject &config, QObject *parent) :
    QObject(parent),
    m_Socket(MakeSocket(config))
{
}

EthConfig::~EthConfig()
{
    m_Socket->close();
    m_Socket->deleteLater();
}

QUdpSocket *EthConfig::MakeSocket(const QJsonObject &config)
{
    QUdpSocket* pSocket;

    if (config.contains("receiver"))
    {
        QJsonObject receiver = config["receiver"].toObject();
        if (receiver.isEmpty())
            throw std::runtime_error("Wrong sender configuratiuon");
        int port = 0;
        if (receiver["port"].isDouble())
            port = receiver["port"].toInt();
        else
            port = receiver["port"].toString().toInt();
        qDebug() << "port is " << port;
        pSocket = new QUdpSocket();
        pSocket->bind(QHostAddress::Any, port);
        qDebug() << "socket state is " << pSocket->state();
        int frequency;
        if (receiver["frequency"].isDouble())
            frequency = receiver["frequency"].toInt();
        else
            frequency =  receiver["frequency"].toString("5").toInt();

    }
    else if (config.contains("sender"))
    {
        QJsonObject sender = config["sender"].toObject();
        if (sender.isEmpty())
            throw std::runtime_error("Wrong sender configuratiuon");
        QString ip = sender["ip"].toString();
        int port = 0;
        if (sender["port"].isDouble())
            port = sender["port"].toInt();
        else
            port = sender["port"].toString().toInt();
        qDebug() << "port is " << port;
        pSocket = new QUdpSocket();
        pSocket->connectToHost(ip, port);
        qDebug() << "socket state is " << pSocket->state();
        int frequency;
        if (sender["frequency"].isDouble())
            frequency = sender["frequency"].toInt();
        else
            frequency =  sender["frequency"].toString("5").toInt();
    }

    return pSocket;
}

ListenEthernet::ListenEthernet(const QJsonObject &config) : EthConfig(config)
{
    connect(m_Socket, &QUdpSocket::readyRead, this, &ListenEthernet::readData);
    qDebug() << "eth constr thread is " << QThread::currentThreadId();
}

void ListenEthernet::readData()
{
    while (m_Socket->hasPendingDatagrams())
    {
        m_baDatagram.resize(m_Socket->pendingDatagramSize());
        m_Socket->readDatagram(m_baDatagram.data(), m_baDatagram.size());
    }
    emit gotData(m_baDatagram);

}

WriteEthernet::WriteEthernet(const QJsonObject &config) : EthConfig(config)
{

}



void WriteEthernet::sendData(const OperateData& data)
{
    m_Socket->write(reinterpret_cast<const char*>(&data), sizeof(data));
}
