#pragma once

#include <QStandardItemModel>
#include <QVariantMap>
#include <QList>
#include <QMap>
#include <QObject>


#include "./CommonDefinition/definition.h"

using namespace AppDefinition::BINS;

class BINSDataModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit BINSDataModel(QObject* parent = 0);

    void init(const QStringList& labels); // Использовать один раз!!

    void fromMap(const QVariantMap& inputData);

    QVariantMap toMap();

signals:

    void dataUpdate(const QVariantMap& inputData);

};



