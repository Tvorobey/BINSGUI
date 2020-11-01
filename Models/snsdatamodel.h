#ifndef SNSDATAMODEL_H
#define SNSDATAMODEL_H

#include <QStandardItemModel>
#include <QVariantMap>

#include "./CommonDefinition/definition.h"

using namespace AppDefinition::SNS;

class SNSDataModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit SNSDataModel(QObject* parent = 0);

public:

    void init(const QStringList& labels);

public:
    void fromMap(const QVariantMap& inputData);

    QVariantMap toMap();

signals:

    void dataUpdate(QVariantMap data);
};

#endif // SNSDATAMODEL_H
