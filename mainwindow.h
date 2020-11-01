#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

#include "./CommonDefinition/definition.h"
#include "Utilities/configreader.h"

#include "Models/binsdatamodel.h"
#include "Models/snsdatamodel.h"
#include "Models/lagdatamodel.h"

#include "Handlers/handlerrectofile.h"
#include "Handlers/databinscollector.h"

//class BINSDataModel;
//class SNSDataModel;

using namespace AppDefinition::JSONFileNames;

typedef const QPair<QString, QString>& coordinatePair;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateModelBINS(const QVariantMap& inputData);
    void updateModelSNS(const QVariantMap& inputData);
    void updateModelLag(const QVariantMap& inputData);

    QPair<float, float> getSNSLatitudeAndLongitude();

    void setCoordinateInputValue(coordinatePair pair);

private:
    Ui::MainWindow *ui;

private:

    QSharedPointer<BINSDataModel>   m_ModelBINS;
    QScopedPointer<SNSDataModel>    m_ModelSNS;
    QScopedPointer<LagDataModel>    m_ModelLag;

private:

    QScopedPointer<HandlerRecToFile>    m_FileRecord;

    QMap<QString, QVariant> test
    {
        {"phi", 2},
        {"lyambda", 32.4876},
        {"heading", 180},
        {"pitch", 20.3675},
        {"roll", -20},
        {"speedNorth", 5.12},
        {"speedEast", -2},
        {"ConnWithBINS", false},
        {"InitCoordinate", false},
        {"ReadyStatus", true},
        {"BINSRegim", "Исправен"},
        {"LagDataStatus", true},
        {"SNSDataStatus", false}
    };

private:

    void keyPressEvent(QKeyEvent *event);

    void setupUIAndModel();

signals:

    void changeCoordianteSource(size_t idx);
    void applyChanges(QPair<float, float> inputData);
    void resetBINS();
    void changeSpeedPriority(size_t idx);
    void changeOperatorInputMethod();

};

#endif // MAINWINDOW_H
