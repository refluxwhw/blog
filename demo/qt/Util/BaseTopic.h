#ifndef BASETOPIC_H
#define BASETOPIC_H

#include <vector>
#include <map>
#include "IObserver.h"
#include "XLock.h"

namespace Util {
    class BaseTopic
    {
    public:
        BaseTopic();

        virtual void addObserver(IObserver* o);
        virtual void removeObserver(IObserver* o);

    private:
        void notifyObservers();

    protected:
        std::vector<IObserver*> m_observers;
        XLock m_lock;
    }; // end of class BaseTopic
} // end of namespace Util

#endif // BASETOPIC_H
