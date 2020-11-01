#ifndef INTERFACEANDDATA_H
#define INTERFACEANDDATA_H

#include "./CommonDefinition/definition.h"
#include "Threads/threadwrapper.h"

#include "Handlers/handlerdatabins.h"
#include "Handlers/handlerdatasns.h"
#include "Handlers/handlerdatalag.h"

#include "Utilities/configreader.h"
#include "mainwindow.h"
#include "Handlers/databinscollector.h"

#include <QScopedPointer>

using namespace AppDefinition::JSONFileNames;

class InterfaceAndData  : public QObject
{
    Q_OBJECT
public:
    InterfaceAndData(QObject* parent = 0);

private:

    QScopedPointer<MainWindow>  m_interface;

    double  m_initLatitude,
            m_initLongitude;

private:
    ThreadWrapper<DataBINSCollector> m_collerctor;
    ThreadWrapper<HandlerDataBINS>  m_HandlerBINS;
    ThreadWrapper<HandlerDataSNS>   m_HandlerSNS;
    ThreadWrapper<HandlerDataLag>   m_HandlerLag;

private:

    void getInitCoordinateFromFile();

    void init();

};

#endif // INTERFACEANDDATA_H
