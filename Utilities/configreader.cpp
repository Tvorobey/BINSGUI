#include "configreader.h"
#include <QFile>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <stdexcept>

configreader::configreader(const std::string& fileName)
{
    QFile loadFile(fileName.data());    //  Просто файл, ничем не примечательный
    if (!loadFile.open(QIODevice::ReadOnly))    //  Нам его только читать - писать конфигурацию мы тут не будем
    {
        throw  std::runtime_error ("Could not open configuration file " + loadFile.fileName().toStdString()); //  Нет такого файла
    }

    QByteArray rawData = loadFile.readAll();    //  Прочитали ВЕСЬ конфиг
    m_confFile = QJsonDocument::fromJson(rawData);  //  Попробовали, получается ли из этого QJsonFile
    loadFile.close();   //  файл можно уже закрыть
    if (m_confFile.isObject())  //  Если это объект...
        m_JSONConfig = m_confFile.object(); //  ...то он то     нам и нужен
    else
    {   //  А иначе конфигурации нет, и что делать дальше - неясно
        throw std::runtime_error ("There is no JSON configuration in " + fileName);
    }
    PopulateConfigs(m_JSONConfig);  //  Ок, давайте попробуем всё это разобрать
}

void configreader::Print() const
{
    for (auto proto : m_configs)
    {
        qDebug() << proto.first.data();
    }
}

QJsonObject configreader::value(const std::string key) const
{
    if (m_configs.find(key)!=m_configs.end())   //  Если ключ нашёлся...
        return m_configs.at(key);   //  ...мы вернём значение (at - потому, что метод константный)
    else    //  А если нет - выбросим ошибку
        throw std::runtime_error ("There is no configuration for device " + key);
}

void configreader::PopulateConfigs(const QJsonObject& object, std::string upperName)
{
    QList<QString> keys = object.keys();    // Выдернули из объекта весь список ключей
    if (keys.contains(QString("type")) ||
            keys.contains(QString("sender")) ||
            keys.contains(QString("receiver")))     //  Есть ли там ключ type?
    {   //  Есть - значит, это уже конечное устройство, и дальше разбираться не будем
        m_configs.insert(std::pair<std::string, QJsonObject>(upperName, object));
        return;
    }
    else
    {   //  а вот если нет ключа type, то...
        for (auto& key : keys)  //  в цикле по ключам
        {
            QJsonObject tmpObject = object[key].toObject(); //  Вытаскивам соответствующий ключу объект
            if (!tmpObject.isEmpty())   //  Если он не пустой
            {   //  Вызываем функцию рекурсивно, передав в качестве имени предыдущего уровня ключ
                PopulateConfigs(tmpObject, upperName.empty() ?
                                    key.toStdString() : //  для первого уровня имя просто ключ
                                    upperName+"."+key.toStdString());   //  для последующих - комбинация с предыдущими
                                                                        //  вида key1.key11.key111
            }
        }
    }
}

std::list<std::string> configreader::values() const
{
    std::list<std::string> keys;
    for (auto config : m_configs)
        keys.push_back(config.first);
    return keys;
}
