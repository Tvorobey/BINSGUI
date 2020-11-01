#include "handlerrectofile.h"
#include <QDebug>

HandlerRecToFile::HandlerRecToFile(QObject *parent) : QObject(parent)
{
    createDir();
}

void HandlerRecToFile::setModel(QSharedPointer<BINSDataModel> &other)
{
    m_model = other;
}

void HandlerRecToFile::prepareFileToRecord(const QString &fileName)
{
    m_dataFile.reset(new QFile(FOLDERNAME + "/" + fileName));

    configAndOpenFile(m_dataFile.data());

    setDescriptionHeader(TableLabels);

    m_recTimer = startTimer(1000);
}

void HandlerRecToFile::stopRecord()
{
    if (m_dataFile.data() != nullptr)
    {
        killCurrentTimer();
        m_dataFile.data()->close();
        m_dataFile.reset();
    }
}

void HandlerRecToFile::createDir()
{
    QDir _folder;

    if (_folder.exists(FOLDERNAME))
        qDebug() << "Falder already exist";
    else if (_folder.mkpath(FOLDERNAME))
    {
        qDebug() << "Create folder";
    }

}

void HandlerRecToFile::setDescriptionHeader(const QStringList &headerLabels)
{
    QByteArray array;

    for (auto i = headerLabels.constBegin(), e = headerLabels.constEnd(); i != e; i++)
    {
        array.append(*i + ";");
    }

    array.append("\n");

    m_dataFile.data()->write(array);
    m_dataFile.data()->flush();
}

void HandlerRecToFile::configAndOpenFile(QFile *file)
{
    if (!file->exists())
        file->open(QIODevice::Append|QIODevice::Text);
    else
    {
        file->remove();
        file->open(QIODevice::Append|QIODevice::Text);
    }
}

void HandlerRecToFile::recDataToFile()
{
    QByteArray array;

    QVariantMap map = m_model.data()->toMap();

    size_t _idx = 0;

    for (auto i = map.constBegin(), e = map.constEnd(); i != e; ++i)
    {
        array.append(map.value(LABELS.value(_idx)).toString());
        array.append(";");
        ++_idx;
    }

    array.append("\n");

    m_dataFile.data()->write(array);
    m_dataFile.data()->flush();
}

void HandlerRecToFile::timerEvent(QTimerEvent *event)
{
    int _timerId = event->timerId();

    if (_timerId == m_recTimer)
        recDataToFile();
}

void HandlerRecToFile::killCurrentTimer()
{
    if (m_recTimer != -1)
    {
        killTimer(m_recTimer);
        m_recTimer = -1;
    }

}
