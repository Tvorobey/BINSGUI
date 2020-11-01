#include "lock.h"
#include <QDebug>

Lock::Lock(QMutex *pm) :
    mutexPtr(pm, [this](QMutex *pm){mutexPtr.get()->unlock();})
{
    mutexPtr.get()->lock();
}



