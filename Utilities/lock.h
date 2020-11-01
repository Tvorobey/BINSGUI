#ifndef LOCK_H
#define LOCK_H

#include <QMutex>
#include <memory>

/*!
 * \brief Класс - Lock
 * \details Класс служит для того, чтобы можно было
 * не беспокоиться о том, что забудешь открыть заново мьютекс
 * Достаточно создать объект этого класса, в параметр бросить
 * указатель на мьютек. При выходе из функции функция чистильщика
 * shared_ptr, откроет мьютекс сама
 */

class Lock
{
public:
    Lock(QMutex *pm);

private:

    std::shared_ptr<QMutex> mutexPtr;
};

#endif // LOCK_H
