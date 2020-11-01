#include "interfaceanddata.h"

namespace
{
    const QString   configFromBINS  = "FromBINS";
    const QString   configToBINS    = "ToBINS";
    const QString   configFromSNS   = "FromSNS";
    const QString   configFromLag   = "FromLag";
}

InterfaceAndData::InterfaceAndData(QObject *parent) : QObject(parent),
    m_interface(new MainWindow())
{

    init();

    connect(m_HandlerBINS.protocol(), &HandlerDataBINS::dataReady, this,
            [this](const QMap<QString, QVariant>& data)
    {
        m_interface.data()->updateModelBINS(data);
    });

    connect(m_HandlerSNS.protocol(), &HandlerDataSNS::dataReady, this,
            [this](const QVariantMap& data)
    {
        m_interface.data()->updateModelSNS(data);
    });

    connect(m_HandlerLag.protocol(), &HandlerDataLag::dataReady, this,
            [this](const QVariantMap& data)
    {
        m_interface.data()->updateModelLag(data);
    });

    connect(m_collerctor.protocol(), &DataBINSCollector::takeLatitudeAndLongitude,
            [this]()
    {
        m_collerctor.protocol()->setInitLatitudeAndLongitude(
                    m_interface.data()->getSNSLatitudeAndLongitude());
    });


    // Сигналы от интерйеса о действиях пользователя
    connect(m_interface.data(), &MainWindow::changeCoordianteSource,
            m_collerctor.protocol(), &DataBINSCollector::setCoordinateSource, Qt::QueuedConnection);
    connect(m_interface.data(), &MainWindow::applyChanges,
            m_collerctor.protocol(), &DataBINSCollector::setInitLatitudeAndLongitude, Qt::QueuedConnection);
    connect(m_interface.data(), &MainWindow::resetBINS,
            m_collerctor.protocol(), &DataBINSCollector::setResetState);
    connect(m_interface.data(), &MainWindow::changeSpeedPriority,
            m_collerctor.protocol(), &DataBINSCollector::setSpeedCorrectionPriority, Qt::QueuedConnection);
    connect(m_interface.data(), &MainWindow::changeOperatorInputMethod,
            [this]()
    {
        m_interface.data()->setCoordinateInputValue(QPair<QString, QString>(QString::number(m_initLatitude), QString::number(m_initLongitude)));
    });
}

void InterfaceAndData::getInitCoordinateFromFile()
{
    configreader reader(REPERDATA);
    QJsonObject config = reader.fullConfig();

    m_initLatitude = config["latitude"].toDouble();
    m_initLongitude = config["longitude"].toDouble();
}

void InterfaceAndData::init()
{
    m_interface.data()->show();

    getInitCoordinateFromFile();

    m_interface.data()->setCoordinateInputValue(QPair<QString, QString>(QString::number(m_initLatitude), QString::number(m_initLongitude)));

    configreader    reader(CONNECTION);
    QJsonObject config = reader.value(configFromBINS);

    m_HandlerBINS.configureAndStart(config);

    config = reader.value(configToBINS);
    m_collerctor.configureAndStart(config);

    m_collerctor.protocol()->setInitLatitudeAndLongitude(QPair<float, float>(static_cast<float>(m_initLatitude), static_cast<float>(m_initLongitude)));

    config = reader.value(configFromSNS);
    m_HandlerSNS.configureAndStart(config);

    config = reader.value(configFromLag);
    m_HandlerLag.configureAndStart(config);

}
