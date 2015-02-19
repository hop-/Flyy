#ifndef _EVENTS_HPP_
#define _EVENTS_HPP_

namespace Flyy
{
    class ID
    {
        static int m_count;
        const int m_id;
    public:
        ID();
        int operator()() const;
    };

    class BaseEvent
    {
        virtual int getType() = 0;
    };

    template <class T>
    class Event :
        public BaseEvent
    {
    public:
        static const ID type;
        int getType();
    };
}

#endif //_EVENTS_HPP_
