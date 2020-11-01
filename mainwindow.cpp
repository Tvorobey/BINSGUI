#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_ModelBINS(new BINSDataModel(parent)),
    m_ModelSNS(new SNSDataModel(parent)),
    m_ModelLag(new LagDataModel(parent)),
    m_FileRecord(new HandlerRecToFile(parent))
{
    setupUIAndModel();

    // Подписываемся на событие обновление модели
    connect(m_ModelBINS.data(), &BINSDataModel::dataUpdate,
            ui->widgetBINSInfo, &InfoFromBINSUI::fromMap);
    connect(m_ModelBINS.data(), &BINSDataModel::dataUpdate,
            ui->widgetConnState, &ConnectionWithBINSUI::fromMap);

    // Управление записью по нажатию на кнопку
    connect(ui->widgetRecControl, &RecControlUI::recStatusChanged, this,
            [this](bool isRec, const QString& fileName)
    {
        if (isRec == true)
            m_FileRecord.data()->prepareFileToRecord(fileName);
        else
            m_FileRecord.data()->stopRecord();
    });

    // Установка текста инпутов широты и долготы из файла
    connect(ui->widgetBINSParam, &BINSParamUI::changeOperatorInputMethod,
            this, &MainWindow::changeOperatorInputMethod);

    // Работа с управляющим сообщением для БИНС
    connect(ui->widgetBINSParam, &BINSParamUI::changeCoordinateSource,
            this, &MainWindow::changeCoordianteSource);
    connect(ui->widgetBINSParam, &BINSParamUI::applyChanges,
            this, &MainWindow::applyChanges);
    connect(ui->widgetBINSParam, &BINSParamUI::resetBINS,
            this, &MainWindow::resetBINS);
    connect(ui->widgetCorrControl, &CorrectionControlUI::changeSpeedPriority,
            this, &MainWindow::changeSpeedPriority);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// NOTE: Почти 3 одинаковые функции, может сделать по типу мульти метода

void MainWindow::updateModelBINS(const QVariantMap &inputData)
{
    m_ModelBINS.data()->fromMap(inputData);
}

void MainWindow::updateModelSNS(const QVariantMap &inputData)
{
    m_ModelSNS.data()->fromMap(inputData);
}

void MainWindow::updateModelLag(const QVariantMap &inputData)
{
    m_ModelLag.data()->fromMap(inputData);
}

QPair<float, float> MainWindow::getSNSLatitudeAndLongitude()
{
    return QPair<float, float>(m_ModelSNS.data()->data(m_ModelSNS.data()->index(0,0)).toFloat(),
                               m_ModelSNS.data()->data(m_ModelSNS.data()->index(1,0)).toFloat());
}

void MainWindow::setCoordinateInputValue(coordinatePair pair)
{
    ui->widgetBINSParam->fillInputFromFile(pair);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F1)
        ui->mainTabWidget->setCurrentIndex(0);
    if (event->key() == Qt::Key_F2)
        ui->mainTabWidget->setCurrentIndex(1);
}

void MainWindow::setupUIAndModel()
{
    ui->setupUi(this);

    m_ModelBINS.data()->init(AppDefinition::BINS::TableLabels);

    m_ModelSNS.data()->init(AppDefinition::SNS::TableLabels);

    m_ModelLag.data()->init(AppDefinition::LAG::TableLabels);

    ui->widgetOutsideData->setModelSNS(m_ModelSNS.data());

    ui->widgetOutsideData->setModelLag(m_ModelLag.data());

    m_FileRecord.data()->setModel(m_ModelBINS);
}




