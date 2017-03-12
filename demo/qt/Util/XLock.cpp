#include "XLock.h"

namespace Util {
#ifdef WIN32
    XLock::XLock() {
        InitializeCriticalSection(&m_cs);
    }
    XLock::~XLock() {
        DeleteCriticalSection(&m_cs);
    }
    void XLock::lock() {
        EnterCriticalSection(&m_cs);
    }
    void XLock::unlock() {
        LeaveCriticalSection(&m_cs);
    }
#else
    XLock::XLock() { pthread_mutex_init(&m_mutex, NULL); }
    XLock::~XLock() { pthread_mutex_destroy(&m_mutex); }
    void XLock::lock() { pthread_mutex_lock(&m_mutex); }
    void XLock::unlock() { pthread_mutex_unlock(&m_mutex); }
#endif
}
