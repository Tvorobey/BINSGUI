#include "binsparamui.h"
#include "ui_binsparamui.h"

BINSParamUI::BINSParamUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BINSParamUI),
    m_LatInput(new LabelWithLineEdit("Начальная широта, град.")),
    m_LonInput(new LabelWithLineEdit("Начальная долгота, град.")),
    m_radioHow(new DefaultRadioBtnGroup(QPair<QString, QString>("Ручной Ввод","Ввод из файла"))),
    m_radioWho(new DefaultRadioBtnGroup(QPair<QString, QString>("Оператор","СНС")))
{
    ui->setupUi(this);

    configUI();
    setUIState();

    connect(m_radioHow.data(), &DefaultRadioBtnGroup::btnClicked,
            this, &BINSParamUI::setInputState);

    connect(m_radioWho.data(), &DefaultRadioBtnGroup::btnClicked,
            this, &BINSParamUI::setSubFormState);

    // Сообщили о том, что мы потвердили то, что ввели в инпуты широты и долготы,
    // Для начальной выставки БИНС
    connect(ui->btnApply, &QPushButton::clicked, this, [this]()
    {
        emit applyChanges(QPair<float, float>(static_cast<float>(m_LatInput.data()->getValue()),
                                              static_cast<float>(m_LonInput.data()->getValue())));
    });

    // Сообщили о том, что надо перезагрузить БИНС
    connect(ui->btnRestartBINS, &QPushButton::clicked, this, [this]()
    {
        emit resetBINS();
    });
}

BINSParamUI::~BINSParamUI()
{
    delete ui;
}

void BINSParamUI::configUI()
{
    ui->verticalLayoutMain->insertWidget(1, m_radioWho.data());

    ui->verticalLayoutGroupBox->insertWidget(0, m_LatInput.data());
    ui->verticalLayoutGroupBox->insertWidget(1, m_LonInput.data());

    ui->verticalLayoutGroupBox->insertWidget(2, m_radioHow.data());
}

void BINSParamUI::setUIState()
{
    m_radioWho.data()->setCheckedBtn(0);    // Данные вводит оператор
    m_radioHow.data()->setCheckedBtn(1);    // Данные вводятся из файла

    setInputState(1);
}

void BINSParamUI::clearInput()
{
    m_LatInput.data()->clear();
    m_LonInput.data()->clear();
}

void BINSParamUI::setInputState(size_t id)
{
    clearInput();

    switch (id)
    {
        case 0:
        {
            m_LatInput.data()->enableInput();
            m_LonInput.data()->enableInput();
        }
            break;
        case 1:
        {
            m_LatInput.data()->disableInput();
            m_LonInput.data()->disableInput();

            emit changeOperatorInputMethod();
        }
            break;
        default:
            break;
    }
}

void BINSParamUI::fillInputFromFile(const QPair<QString, QString>& inputText)
{
    m_LatInput.data()->setValue(inputText.first);
    m_LonInput.data()->setValue(inputText.second);
}

void BINSParamUI::setSubFormState(size_t id)
{
    switch (id)
    {
        case 0:
        {
            m_LatInput.data()->enableInput();
            m_LonInput.data()->enableInput();

            m_radioHow.data()->setButtonsState("enable");

            ui->btnApply->setDisabled(false);

            m_radioHow.data()->setCheckedBtn(0);

            clearInput();
        }
            break;
        case 1:
        {
            m_LatInput.data()->disableInput();
            m_LonInput.data()->disableInput();

            m_radioHow.data()->setButtonsState("disable");

            ui->btnApply->setDisabled(true);
        }
            break;

        default:
            break;
    }

    emit changeCoordinateSource(id);

}
