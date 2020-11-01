#ifndef OUTSIDESYSTEMINFO_H
#define OUTSIDESYSTEMINFO_H

#include <QWidget>
#include <functional>
#include <QMap>
#include <QAbstractItemModel>

#include "./CommonDefinition/definition.h"

using namespace AppDefinition::SNS;

namespace Ui {
class OutsideSystemInfo;
}

class OutsideSystemInfo : public QWidget
{
    Q_OBJECT

public:
    explicit OutsideSystemInfo(QWidget *parent = 0);
    ~OutsideSystemInfo();

    void setModelSNS(QAbstractItemModel* model);
    void setModelLag(QAbstractItemModel* model);

private:
    Ui::OutsideSystemInfo *ui;
};

#endif // OUTSIDESYSTEMINFO_H
