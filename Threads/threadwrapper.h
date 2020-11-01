#ifndef THREADWRAPPER_H
#define THREADWRAPPER_H

#include <QtWidgets/QApplication>
#include <QJsonObject>
#include <QLoggingCategory>
#include <QThread>
#include <assert.h>

template <typename Protocol>
class ThreadWrapper
{
public:
    /**
     * @brief Конструктор ThreadWrapper по умаолчанию. Создаёт класс с пустым протоколом обмена
     */
    ThreadWrapper()
    {
        m_protocol = nullptr;

        //перед закрытием приложения обязательно останавливаем все потоки драйверов
        QObject::connect(qApp,&QCoreApplication::aboutToQuit,[this]{stop();});
    }

    /**
     * @brief Конструктор ThreadWrapper с конфигурационным параметром.
     * @details Создаёт экземпляр врапера с протоколом, инициализированным конфигурационным параметром,
     * и инициализирует поток обмена.
     * @param config Конфигурация для протокола
     * @sa SimpleProtocol
     */
    explicit ThreadWrapper(const QJsonObject &config)
        :ThreadWrapper<Protocol>()
    {
        m_protocol = new Protocol(config);
        //перемещаем протокол в поток
        initThread();
    }

    ~ThreadWrapper()
    {
        stop();
    }

    /**
     * @brief Функция configureAndStart запускает протокол из конфигурационного файла
     * @details Основное назначение данной функции - создание и запуск сконфигурированного
     * протокола для ThreadWrapper, созданного конструктором по умолчанию. В случае, если
     * конфигурация уже была создана и поток был запущен, поток останавливается, создаётся
     * новый протокол и выполняется запуск
     * @param [in] config
     */
    virtual void configureAndStart(QJsonObject config)
    {
        //  Вызовем stop() в любом случае
        stop();
        if (m_protocol) //  Если протокол уже был, его надо удалить
            delete m_protocol;
        //  создаём новый протокол
        m_protocol = new Protocol(config);
        //перемещаем протокол в поток
        initThread();

        //запускаем поток
        start();
    }

    /**
     * @brief Функция start запускает уже настроенный протокол.
     * @details Если протокол был запущен, производится перезапуск. Если протокол
     * пустой, поток не запускается и выводится диагностическое сообщение.
     */
    virtual void start()
    {
        //останавливаем поток, если он запущен
        stop();

        if (m_protocol != nullptr)
            thread.start();
        else
            qWarning() << "[ThreadWrapper] Protocol is not set. Cannot start";
    }
    /**
     * @brief Функция stop останавливает поток, если он был запущен.
     */
    virtual void stop()
    {
        if (thread.isRunning())
        {
            //останавливаем поток
            thread.quit();
            thread.wait();
        }
    }


    /**
     * @brief Метод protocol указаетль на обёртываемый в поток протокол.
     * @details Основное назначение данной функции - добраться до функций
     * конвертирования, реализованных внутри протокола.
     * @return указатель на протокол
     */
    Protocol* protocol() const
    {
        return m_protocol;
    }

    QMap<QString,QVariant> dictionary()
        {
//            if (m_protocol != nullptr)
                return m_protocol->dictionary();
//            else
//                return nullptr;
        }


private:
    /// Инициализация потока
    void initThread()
    {
        //перемещаем протокол в поток и запускаем поток
        m_protocol->moveToThread(&thread);
        QObject::connect(&thread, &QThread::started, m_protocol, &Protocol::initAndStart);

    }

    ///инстанс протокола
    Protocol *m_protocol;
    ///поток, в котором выполняется драйвер
    QThread thread;
    //запрещаем конструктор копирования и присваивание
    ThreadWrapper & operator= (const ThreadWrapper&) = delete;
    ThreadWrapper(const ThreadWrapper&) = delete;
};

#endif // THREADWRAPPER_H
