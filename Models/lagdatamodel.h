#pragma once

#include <QStandardItemModel>
#include <QVariantMap>

#include "./CommonDefinition/definition.h"

using namespace AppDefinition::LAG;

class LagDataModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit LagDataModel(QObject* parent = 0);

public:

    void init(const QStringList& labels);

public:
    void fromMap(const QVariantMap& inputData);

    QVariantMap toMap();

signals:

    void dataUpdate(QVariantMap data);
};

