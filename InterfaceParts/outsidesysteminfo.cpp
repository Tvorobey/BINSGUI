#include "outsidesysteminfo.h"
#include "ui_outsidesysteminfo.h"

OutsideSystemInfo::OutsideSystemInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutsideSystemInfo)
{
    ui->setupUi(this);

    ui->SNSView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->SNSView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QFont font = ui->SNSView->verticalHeader()->font();
    font.setPointSize(11);

    ui->SNSView->verticalHeader()->setFont(font);

    ui->LagView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->LagView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    font = ui->LagView->verticalHeader()->font();
    font.setPointSize(11);

    ui->LagView->verticalHeader()->setFont(font);


}

OutsideSystemInfo::~OutsideSystemInfo()
{
    delete ui;
}

void OutsideSystemInfo::setModelSNS(QAbstractItemModel *model)
{
    ui->SNSView->setModel(model);
}

void OutsideSystemInfo::setModelLag(QAbstractItemModel *model)
{
    ui->LagView->setModel(model);
}

