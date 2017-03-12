#ifndef XLOCK_H
#define XLOCK_H

#ifdef WIN32
#  include <Windows.h>
#else
#  include <pthread.h>
#endif

namespace Util {
    class XLock
    {
    public:
        XLock();
        ~XLock();
        void lock();
        void unlock();

    private:
#ifdef WIN32
        CRITICAL_SECTION m_cs;
#else
        pthread_mutex_t m_mutex;
#endif
    }; // end of XLock
} // end of namespace Util

#endif // XLOCK_H
