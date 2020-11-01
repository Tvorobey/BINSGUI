#ifndef DATABINSCOLLECTOR_H
#define DATABINSCOLLECTOR_H

#include <QObject>
#include <QPair>
#include <QString>
#include <bitset>
#include <QVariantMap>
#include <QDebug>
#include <QTimer>
#include <QTimerEvent>

#include "./CommonDefinition/definition.h"
#include "./ConnectionConfig/ethconfig.h"

using namespace AppDefinition::controlBINS;
/*!
 * \brief The DataBINSCollector class
 * \details - Данный класс служит для сбора данных, необхожимых для
 * управления БИНС. Эти данные он собирает с формы (инпуты и т.д).
 * Также реаигрует на нажатия кнопок (меняет управляющее слово БИНС)
 */

class DataBINSCollector : public QObject
{
    Q_OBJECT
public:
    explicit DataBINSCollector(const QJsonObject& config, QObject *parent = nullptr);

private:

    std::bitset<16> operateWord;

    OperateData     operateData;

    QScopedPointer<WriteEthernet>   m_EthToBINS;

    QJsonObject m_config;

private:

    QScopedPointer<QTimer>  m_sendTimer;

    int  m_requestTimerID;

private:

    void initOperateWord();

    void timerEvent(QTimerEvent* event);
    void killCurrentTimer();

signals:

    void takeLatitudeAndLongitude();

public slots:
    /*!
     * \brief   setCoordinateSource - меняет УС БИНС
     * \param   sourceId - id источника координат для начальной выставки:
     *          0 - Оператор (мы забираем координаты из инпутов, при нажатии "Применить")
     *          1 - СНС (берем данные из модели СНС, по таймеру (?) )
     */
    void setCoordinateSource(size_t sourceId);

    /*!
     * \brief setInitLatitudeAndLongitude
     * \param initCoordinates - первый параметр широта, второй долгота
     */
    void setInitLatitudeAndLongitude(const QPair<float, float> initCoordinates);

    void setResetState();

    /*!
     * \brief setSpeedCorrectionPriority
     * \param idx - 0 - Приоритет скоростей от СНС над лагом
     *              1 - Приоритет скоростей от Лага над СНС
     */
    void setSpeedCorrectionPriority(size_t idx);

    void initAndStart();
};

#endif // DATABINSCOLLECTOR_H
