#include "binsdatamodel.h"
#include <QDebug>

BINSDataModel::BINSDataModel(QObject *parent) :
    QStandardItemModel(parent)
{

}

void BINSDataModel::init(const QStringList &labels)
{
    setHorizontalHeaderLabels(labels);
    setRowCount(1);
}

void BINSDataModel::fromMap(const QVariantMap &inputData)
{
    for (auto i = inputData.constBegin(), e = inputData.constEnd(); i != e; ++i)
    {
        setData(index(0, LABELS.key(i.key())), i.value(), Qt::DisplayRole);
    }

    emit dataUpdate(toMap());
}

QVariantMap BINSDataModel::toMap()
{
    QVariantMap map;

    for (int i = 0; i < columnCount(); ++i)
        map.insert(LABELS.value(i), data(index(0,i), Qt::DisplayRole));

    return std::move(map);
}


