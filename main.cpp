#include <QApplication>
#include <QDebug>

#include "interfaceanddata.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    InterfaceAndData    app;

    return a.exec();
}
