#include "handlerdatalag.h"

HandlerDataLag::HandlerDataLag(const QJsonObject &config, QObject *parent) :
    QObject(parent),
    m_config(config)
{

}

void HandlerDataLag::fillMap()
{
    m_map[SPEED_VX]             = m_data.speed[0];
    m_map[SPEED_VY]             = m_data.speed[1];
    m_map[SPEED_VZ]             = m_data.speed[2];
    m_map[SPEED_VALID]          = m_data.flags.is_altitude_valid ? "Валидна" : "Не валидна";
    m_map[HEIGHT_VALID]         = m_data.flags.is_altitude_valid ? "Валидна" : "Не валидна";
    m_map[REVERBERATION_SOLID]  = m_data.flags.is_volume_solve ? "ДА" : "НЕТ";
    m_map[PWM_ENABLE]           = m_data.flags.is_pwm_global ? "Разрешено" : "Запрещено";

    emit dataReady(m_map);
}

void HandlerDataLag::fillDataStruct(const QByteArray &array)
{
    memcpy(&m_data, array, sizeof(m_data));

    fillMap();
}

void HandlerDataLag::initAndStart()
{
    m_EthFromLag.reset(new ListenEthernet(m_config));

    connect(m_EthFromLag.data(), &ListenEthernet::gotData,
            this, &HandlerDataLag::fillDataStruct);
}
