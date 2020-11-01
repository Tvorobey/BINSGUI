#ifndef configreader_H
#define configreader_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <map>
#include <utility>
#include <string>
#include <list>

class configreader
{
public:

    configreader() = delete;
    /*!
     * \brief configreader Класс для чтения конфигурации
     * \param fileName имя файла, содержащего конфигурацию
     */
    configreader(const std::string& fileName);
    /*!
     * \brief configreader Перегруженый конструктор
     * \param fileName имя файла, содержащего конфигурацию
     */
    configreader(const QString& fileName) : configreader(fileName.toStdString()){;}
    /*!
     * \brief configreader Перегруженый конструктор
     * \param fileName имя файла, содержащего конфигурацию
     */
    configreader(const char* fileName) : configreader(std::string(fileName)){;}

    /*!
     * \brief value Возвращает конфигурацию устройства
     * \details После прочтения конфигурации все устройства, для которых определено поле \it type
     * помещаются в контейнер m_configs. В нём ключом является имя устройства. Устройства на первом уровне
     * имют мобственное имя, например \it sep, на следующем уровне добавляется префикс предыдущего уровня,
     * например, sep.vm6 и т.д.
     * \param key ключ для поиска устройства
     * \return Объект с конфигурацией
     * \throws Если устройство с ключом не найдено, выбрасывается std::runtime_error
     */
    QJsonObject value(const std::string key) const;

    /*!
     * \brief value Перегруженый вариант предыдущей функции
     * \param key ключ для поиска устройства
     * \return Объект с конфигурацией
     * \throws Если устройство с ключом не найдено, выбрасывается std::runtime_error
     */
    QJsonObject value(const QString key) const {return value(key.toStdString());}

    /*!
     * \brief value Перегруженый вариант предыдущей функции
     * \param key ключ для поиска устройства
     * \return Объект с конфигурацией
     * \throws Если устройство с ключом не найдено, выбрасывается std::runtime_error
     */
    QJsonObject value(const char* key) const {return value(std::string(key));}

    /**
     * @brief values    Возвращает список найденых конфигураций
     * @return  список
     */
    std::list<std::string> values() const;

    /*!
     * \brief Print Просто выводит в stdout все найденные конфигурации. Безвредна. Бесполезна.
     */
    void Print() const;

    /*!
     * \brief fullConfig Возвращает корневой конфиг в случаях, когда разбирать его и выделять
     * отдельные конфиги нет необходимости
     * \return Корневой конфиг
     */
    QJsonObject fullConfig() const {return m_JSONConfig;}

protected:
    /*!
     * \brief PopulateConfigs Заполняет контейнер с конфигурациями устройств
     * \details Проверяет, является ли object конечным устройством. Для этого в настоящий момент проверяется наличие поля
     * \it type. При его наличии помещает текущее устройство в контейнер. В противном случае, пытается для каждого найденого
     * в объекте ключа создать под-объект. Если он не пустой, вызывается рекурентно
     * \param object Объект с конфигурацией.
     * \param upperName имя вызывавшего объекта - предыдущего уровня
     */
    void PopulateConfigs(const QJsonObject& object, std::string upperName = std::string());

    QJsonDocument m_confFile; ///< Файл с документом
    QJsonObject m_JSONConfig; ///< Головной объект с конфигурациями
    std::map<std::string, QJsonObject> m_configs;   ///< Разобранные конфигурации
};

#endif // configreader_H
