#ifndef INFOFROMBINSUI_H
#define INFOFROMBINSUI_H

#include <QWidget>
#include <QDebug>
#include <QSharedPointer>
#include <QList>
#include <functional>

#include "./CommonDefinition/definition.h"
// Подключим наши компоненты
#include "labelwithindicator.h"


using Handler = std::function<void(const QVariant&)>;

using namespace AppDefinition::BINS;

namespace Ui {
class InfoFromBINSUI;
}

class InfoFromBINSUI : public QWidget
{
    Q_OBJECT

public:
    explicit InfoFromBINSUI(QWidget *parent = 0);
    ~InfoFromBINSUI();

    void fromMap(const QVariantMap& data);

private:
    Ui::InfoFromBINSUI *ui;

    QList<QSharedPointer<LabelWithIndicator>>   m_InfoBINS;
    QList<QSharedPointer<LabelWithIndicator>>   m_DataStatus;

private:

    void fillList();

    void configUI();

private:

    QMap<QString, Handler>  m_handlers;

};

#endif // INFOFROMBINSUI_H
