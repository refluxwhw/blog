#ifndef AUTOLOCK_H
#define AUTOLOCK_H

#include "XLock.h"

namespace Util {
    class AutoLock
    {
    public:
        inline AutoLock(XLock *lock = NULL) : m_lock(lock) {
            if (NULL != m_lock) { m_lock->lock(); }
        }

        inline ~AutoLock() {
            if (NULL != m_lock) { m_lock->unlock(); }
        }

    private:
        XLock *m_lock;
    }; // end of class AutoLock
} // end of namespace Util

#endif // AUTOLOCK_H
