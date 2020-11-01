#include "lagdatamodel.h"

LagDataModel::LagDataModel(QObject *parent) :
    QStandardItemModel(parent)
{

}

void LagDataModel::init(const QStringList &labels)
{
    setVerticalHeaderLabels(labels);
    setColumnCount(1);
}

void LagDataModel::fromMap(const QVariantMap &inputData)
{
    for (auto i = inputData.begin(), e = inputData.end(); i != e; ++i)
        setData(index(LABELS.key(i.key()), 0), i.value(), Qt::DisplayRole);

    emit dataUpdate(toMap());
}

QVariantMap LagDataModel::toMap()
{
    QVariantMap map;

    for (int i = 0; i < columnCount(); ++i)
        map.insert(LABELS.value(i), data(index(i,0), Qt::DisplayRole));

    return std::move(map);
}
