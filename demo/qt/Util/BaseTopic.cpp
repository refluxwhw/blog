#include "BaseTopic.h"
#include "AutoLock.h"

namespace Util {
    BaseTopic::BaseTopic()
    {

    }

    void BaseTopic::addObserver(IObserver *o)
    {
        AutoLock l(&m_lock);
        for (unsigned int i=0; i<m_observers.size(); i++)
        {
            if (o == m_observers[i]) // have exist
            {
                return;
            }
        }

        m_observers.push_back(o);
    }

    void BaseTopic::removeObserver(IObserver *o)
    {
        AutoLock l(&m_lock);
        for (unsigned int i=0; i<m_observers.size(); i++)
        {
            if (o == m_observers[i]) // find it
            {
                m_observers.erase(m_observers.begin() + i);
                return;
            }
        }
    }

    void BaseTopic::notifyObservers()
    {
        AutoLock l(&m_lock);
        for (unsigned int i=0; i<m_observers.size(); i++)
        {
            IObserver* o = m_observers[i];
            o->update(this);
        }
    }

} // end of namespace Util
