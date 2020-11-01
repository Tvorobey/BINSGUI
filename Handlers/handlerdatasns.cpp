#include "handlerdatasns.h"

HandlerDataSNS::HandlerDataSNS(const QJsonObject& config, QObject *parent) :
    QObject(parent),
    m_config(config)
{

}

void HandlerDataSNS::fillMap()
{
    double  tmp     = m_data.latitude;
    int     intTmp  = static_cast<int>(tmp)/100;
    tmp             = (tmp - 100*intTmp)/60.0;
    m_map[LATITUDE] = tmp + intTmp;

    tmp = m_data.longitude;
    intTmp = static_cast<int>(tmp)/100;
    tmp = (tmp - 100*intTmp)/60.0;
    m_map[LONGITUDE]    = tmp + intTmp;

    m_map[ABS_SPEED]    = m_data.absSpeed*0.513745; // Перевели в м/с
    m_map[NORTH_SPEED]  = m_data.northSpeed;
    m_map[EAST_SPEED]   = m_data.eastSpeed;
    m_map[STATUS]       = (m_data.status == 0) ? "Достоверно" : "Не достоверно";

    emit dataReady(m_map);
}

void HandlerDataSNS::fillDataStruct(const QByteArray &array)
{
    memcpy(&m_data, array, sizeof(m_data));

    fillMap();
}

void HandlerDataSNS::initAndStart()
{   
    m_EthFromSNS.reset(new ListenEthernet(m_config));

    connect(m_EthFromSNS.data(), &ListenEthernet::gotData,
            this, &HandlerDataSNS::fillDataStruct);
}
