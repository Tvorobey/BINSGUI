#include "databinscollector.h"

namespace
{
    constexpr int sendTimerFreq = 500;
    constexpr int requestFreq   = 1000;
}

DataBINSCollector::DataBINSCollector(const QJsonObject& config,QObject *parent) :
    QObject(parent),
    m_config(config),
    m_sendTimer(new QTimer(parent)),
    m_requestTimerID(-1)
{
    initOperateWord();

    m_sendTimer.data()->start(sendTimerFreq);
}

void DataBINSCollector::timerEvent(QTimerEvent *event)
{
    auto timerId = event->timerId();

    if(timerId == m_requestTimerID)
        emit takeLatitudeAndLongitude();
}

void DataBINSCollector::killCurrentTimer()
{
    if (m_requestTimerID != -1)
    {
        killTimer(m_requestTimerID);
        m_requestTimerID = -1;
    }
}

void DataBINSCollector::initOperateWord()
{
    operateWord[static_cast<int>(BitDescr::INITIAL_HEAD)]     = 0;    // Режим гирокомпасирования
    operateWord[static_cast<int>(BitDescr::SNS_PRIORITY)]     = 1;    // Приоритет внешней СНС (НЕ ИЗМЕНЯЕТСЯ, так как
                                                    // внутренней у нас НЕ БУДЕТ
    operateWord[static_cast<int>(BitDescr::CHANGE_SNS_PR)]    = 1;    // Изменить приоритет СНС
    operateWord[static_cast<int>(BitDescr::REGIM)] = 1;               // По умолчанию будет стоять режим "ВВОД"
    operateWord[static_cast<int>(BitDescr::SPEED_PRIORITY)]   = 1;    // Приоритет скоростей от Лага
    operateWord[static_cast<int>(BitDescr::CHANGE_LAG_PR)]    = 1;    // Изменить приоритет лага
    operateWord[static_cast<int>(BitDescr::INIT_RESET)]       = 0;    // Обычный режим работы БИНС
    // NOTE: Уточнить какой режим мы используем
    operateWord[static_cast<int>(BitDescr::GIRO_RGM)]         = 0;    // Не использовать режим гироазимута
    operateWord[static_cast<int>(BitDescr::HARD_RESET)]       = 0;    // Обычный режим работы БИНС. Выставим 1, когда будет
                                                    // Команда на перезапуск
    operateWord[static_cast<int>(BitDescr::RS_PRIORITY)]      = 0;    // Всегда считываем высоту из управляющего пакета
    operateWord[static_cast<int>(BitDescr::USE_HEIGHT)]       = 1;    // Режим работы с высотой

    operateData.controlWord = static_cast<float>(operateWord.to_ulong());
}

void DataBINSCollector::setCoordinateSource(size_t sourceId)
{
    switch (sourceId)
    {
        case 0:
        {
            qDebug() << "enter add enter rgm";

            killCurrentTimer();
            operateWord[static_cast<int>(BitDescr::REGIM)] = true; // Режим БИНС - ввод начальных данных
            operateData.controlWord = static_cast<float>(operateWord.to_ulong());
        }
            break;
        case 1:
        {
            qDebug() << "Enter at auto regim";

            operateWord[static_cast<int>(BitDescr::REGIM)] = false; // Режим БИНС - автономность
            operateData.controlWord = static_cast<float>(operateWord.to_ulong());

            m_requestTimerID = startTimer(requestFreq);

        }
            break;
        default:
            break;
    }
}

void DataBINSCollector::setInitLatitudeAndLongitude(const QPair<float, float> initCoordinates)
{
    operateData.initLatitude = initCoordinates.first;
    operateData.initLongitude = initCoordinates.second;
}

void DataBINSCollector::setResetState()
{
    operateWord[static_cast<int>(BitDescr::HARD_RESET)] = 1; // Команда БИНС для перезагрузки
    operateData.controlWord = static_cast<float>(operateWord.to_ulong());
}

void DataBINSCollector::setSpeedCorrectionPriority(size_t idx)
{
    operateWord[static_cast<int>(BitDescr::SPEED_PRIORITY)] = idx;
    operateData.controlWord = static_cast<float>(operateWord.to_ulong());
}

void DataBINSCollector::initAndStart()
{
    m_EthToBINS.reset(new WriteEthernet(m_config));

    connect(m_sendTimer.data(), &QTimer::timeout,
            [this]()
    {
        m_EthToBINS.data()->sendData(operateData);

        operateWord[static_cast<int>(BitDescr::HARD_RESET)]       = 0;
        operateData.controlWord = static_cast<float>(operateWord.to_ulong());
    });
}
