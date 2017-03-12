#ifndef IOBSERVER_H
#define IOBSERVER_H

namespace Util {
    class BaseTopic;
    class IObserver
    {
    public:
        IObserver() {}
        /**
         * @brief notice the topic is changed, and you can do something,
         * You should ensure that this function takes as little as possible.
         * @param topic[BaseTopic*]: which topic is changed
         */
        virtual void update(BaseTopic* topic) = 0;
    };
}


#endif // IOBSERVER_H
