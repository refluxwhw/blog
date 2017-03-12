#ifndef MIXUTIL_H
#define MIXUTIL_H

#if 0

#ifdef WIN32
#  include <Windows.h>
#else
#  include <pthread.h>
#endif

namespace Util {
    /**
     * @brief XLock
     */
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
    };

    /**
     * @brief AutoLock
     */
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
    };
}

#endif // end of if 0
#endif // MIXUTIL_H
