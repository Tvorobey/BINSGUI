#-------------------------------------------------
#
# Project created by QtCreator 2019-11-12T07:50:47
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InterfaceBINS
TEMPLATE = app

CONFIG += c++11

#QMAKE_CXXFLAGS = -Wconversion

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH +=  ./CustomElement \
                ./InterfaceParts

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        ./CustomElement/defaultradiobtngroup.cpp \
        CustomElement/semaphorradiobtngroup.cpp \
        CustomElement/labelwithlineedit.cpp \
        CustomElement/inputfornumber.cpp \
        CustomElement/indicator.cpp \
        CustomElement/labelwithindicator.cpp \
        InterfaceParts/binsparamui.cpp \
        InterfaceParts/infofrombinsui.cpp \
        InterfaceParts/binsremotecontrolui.cpp \
        InterfaceParts/correctioncontrolui.cpp \
        InterfaceParts/reccontrolui.cpp \
        InterfaceParts/connectionwithbinsui.cpp \
        InterfaceParts/outsidesysteminfo.cpp \
        Models/binsdatamodel.cpp \
        ./Threads/threadwrapper.cpp \
        ./Utilities/configreader.cpp \
        ./Utilities/lock.cpp \
        ./ConnectionConfig/ethconfig.cpp \
        Handlers/handlerdatabins.cpp \
        Handlers/handlerrectofile.cpp \
        Handlers/databinscollector.cpp \
    interfaceanddata.cpp \
    Models/snsdatamodel.cpp \
    Handlers/handlerdatasns.cpp \
    Models/lagdatamodel.cpp \
    Handlers/handlerdatalag.cpp

HEADERS += \
        mainwindow.h \
        ./CustomElement/defaultradiobtngroup.h \
        CustomElement/semaphorradiobtngroup.h \
        CustomElement/labelwithlineedit.h \
        CustomElement/inputfornumber.h \
        CustomElement/indicator.h \
        CustomElement/labelwithindicator.h \
        InterfaceParts/binsparamui.h \
        InterfaceParts/infofrombinsui.h \
        InterfaceParts/binsremotecontrolui.h \
        InterfaceParts/correctioncontrolui.h \
        InterfaceParts/reccontrolui.h \
        InterfaceParts/connectionwithbinsui.h \
        InterfaceParts/outsidesysteminfo.h \
        Models/binsdatamodel.h \
        ./Threads/threadwrapper.h \
        ./Utilities/configreader.h \
        ./Utilities/lock.h \
        ./ConnectionConfig/ethconfig.h \
        Handlers/handlerdatabins.h \
        GlobalStruct/exchangestruct.h \
        CommonDefinition/definition.h \
        Handlers/handlerrectofile.h \
        Handlers/databinscollector.h \
    interfaceanddata.h \
    Models/snsdatamodel.h \
    Handlers/handlerdatasns.h \
    Models/lagdatamodel.h \
    Handlers/handlerdatalag.h

FORMS += \
        mainwindow.ui \
        CustomElement/defaultradiobtngroup.ui \
        CustomElement/semaphorradiobtngroup.ui \
        CustomElement/labelwithlineedit.ui \
        CustomElement/indicator.ui \
        CustomElement/labelwithindicator.ui \
        InterfaceParts/binsparamui.ui \
        InterfaceParts/infofrombinsui.ui \
        InterfaceParts/binsremotecontrolui.ui \
        InterfaceParts/correctioncontrolui.ui \
        InterfaceParts/reccontrolui.ui \
        InterfaceParts/connectionwithbinsui.ui \
        InterfaceParts/outsidesysteminfo.ui

