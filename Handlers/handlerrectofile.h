#ifndef HANDLERRECTOFILE_H
#define HANDLERRECTOFILE_H

#include <QObject>
#include <QScopedPointer>
#include <QFile>
#include <QDir>

#include "CommonDefinition/definition.h"
#include "Models/binsdatamodel.h"

using namespace AppDefinition::recFolderParam;
using AppDefinition::BINS::LABELS;

class HandlerRecToFile : public QObject
{
    Q_OBJECT
public:
    explicit HandlerRecToFile(QObject *parent = nullptr);

public:

    void setModel(QSharedPointer<BINSDataModel>& other);

    void prepareFileToRecord(const QString& fileName);
    void stopRecord();

private:

    QScopedPointer<QFile>   m_dataFile;

    QSharedPointer<BINSDataModel>   m_model;

    int m_recTimer;

private:

    void createDir();
    void setDescriptionHeader(const QStringList& headerLabels);
    void configAndOpenFile(QFile* file);

    void recDataToFile();

    void timerEvent(QTimerEvent* event);
    void killCurrentTimer();

signals:

public slots:
};

#endif // HANDLERRECTOFILE_H
