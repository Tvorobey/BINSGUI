#include "handlerdatabins.h"

HandlerDataBINS::HandlerDataBINS(const QJsonObject &config, QObject *parent)
    : QObject(parent),
      m_config(config)
{

}

void HandlerDataBINS::decryptStatusWord(int ComStatusWord, unsigned short EthStatusWord)
{
    m_ComBitCheck = static_cast<int>(ComStatusWord);
    m_EthBitCheck = static_cast<int>(EthStatusWord);
}

void HandlerDataBINS::fillMap()
{

    m_map[PHI] = m_DataBINS.phi;
    m_map[LYAMBDA] = m_DataBINS.lyambda;
    m_map[HEADING] = m_DataBINS.heading;
    m_map[PITCH] = m_DataBINS.pitch;
    m_map[ROLL] = m_DataBINS.roll;
    m_map[SPEEDNORTH] = m_DataBINS.speedNorth;
    m_map[SPEEDEAST] = m_DataBINS.speedEast;
    m_map[READYSTATUS] = bool(m_ComBitCheck[0]); // Начальная выставка - false
                                        // Режим "Навигация" - true

    m_map[INITCOORDINATE] = bool(m_ComBitCheck[1]);  // Начальных данных нет - false
                                            // Начальные данные приняты - true

    m_map[SNSDATASTATUS] = bool(m_ComBitCheck[3]);   // Данные с внешней СНС достоверны/недостоверны
    m_map[LAGDATASTATUS] = bool(m_ComBitCheck[4]);   // Данные с Лаг достоверны/недостоверны
    m_map[CONNWITHBINS] =  bool(m_EthBitCheck[4]) ? false : true;
    m_map[BINSREGIM] = (bool(m_EthBitCheck[5]) && bool(m_EthBitCheck[6])) ? "Автономный" : "Обсервационный";
    m_map[COMCONNECTSTATUS] = m_DataBINS.ComConnection;
}

void HandlerDataBINS::workWithData(const QByteArray &array)
{
    memcpy(&m_DataBINS, array, sizeof(m_DataBINS));

    decryptStatusWord(m_DataBINS.COMStatusWord, m_DataBINS.ethStatusWord);

    fillMap();


    emit dataReady(m_map);
}

void HandlerDataBINS::initAndStart()
{
    m_EthFromBINS.reset(new ListenEthernet(m_config));

    connect(m_EthFromBINS.data(), &ListenEthernet::gotData,
            this, &HandlerDataBINS::workWithData);
}
