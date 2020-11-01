#include "reccontrolui.h"
#include "ui_reccontrolui.h"

RecControlUI::RecControlUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecControlUI)
{
    ui->setupUi(this);

    setFileName();

    connect(ui->btnStartRecord, &QPushButton::clicked,
            this, &RecControlUI::changeState);
}

RecControlUI::~RecControlUI()
{
    delete ui;
}

void RecControlUI::setFileName(const QDate &date, const QTime &time)
{
    ui->lineEditFileName->setText("BINS_" + QString::number(date.day())
                                  + QString::number(date.month())
                                  + QString::number(date.year()) + "_"
                                  + QString::number(time.hour())
                                  + QString::number(time.minute())
                                  + QString::number(time.second()) + ".dat");
}

void RecControlUI::changeState(bool clicked)
{
    Q_UNUSED(clicked);

    if (ui->btnStartRecord->text() == "Прекратить запись")
        setFileName();

    ui->btnStartRecord->setText((ui->btnStartRecord->text() == "Начать запись") ?
                                    "Прекратить запись" : "Начать запись");

    ui->lineEditFileName->setDisabled((ui->btnStartRecord->text() == "Начать запись") ?
                                          false : true);

    emit recStatusChanged((ui->btnStartRecord->text() == "Начать запись") ?
                            false : true, ui->lineEditFileName->text());

}
