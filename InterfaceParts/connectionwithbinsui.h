#ifndef CONNECTIONWITHBINSUI_H
#define CONNECTIONWITHBINSUI_H

#include <QWidget>
#include <QSharedPointer>
#include <QList>

#include "labelwithindicator.h"
#include "./CommonDefinition/definition.h"

namespace Ui {
class ConnectionWithBINSUI;
}

using Handler = std::function<void(const QVariant&)>;

using namespace AppDefinition::BINS;

class ConnectionWithBINSUI : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectionWithBINSUI(QWidget *parent = 0);
    ~ConnectionWithBINSUI();

    void fromMap(const QVariantMap& data);

private:
    Ui::ConnectionWithBINSUI *ui;

    QList<QSharedPointer<LabelWithIndicator>>   m_ConnectionState;

private:

    void fillList();
    void configUI();

private:

    QMap<QString, Handler>  m_handlers;
};

#endif // CONNECTIONWITHBINSUI_H
