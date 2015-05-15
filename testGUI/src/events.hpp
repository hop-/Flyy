#ifndef _EVENTS_HPP_
#define _EVENTS_HPP_

namespace Flyy
{
        class ID
        {
                static int m_count;
                const int m_id;
        public:
                ID() :
                        m_id(++m_count)
                {}
                inline int operator()() const
                {
                        return m_id; 
                }
        };
        
        class BaseEvent
        {
        public:
                virtual int getType() = 0;
                virtual ~BaseEvent(){};
        };

        template <class T>
        class Event :
                public BaseEvent
        {
        public:
                static const ID type;
                inline int getType()
                {
                        return type();
                }
        };

        template<class T>
        const ID Event<T>::type;

        class EventQuit :
                public Event<EventQuit>
        {};

        class EventReset :
                public Event<EventReset>
        {};

        class IncreaseWarpingEvent :
                public Event<IncreaseWarpingEvent>
        {};

        class DecreaseWarpingEvent :
                public Event<DecreaseWarpingEvent>
        {};

        class EventPlayerUp :
                public Event<EventPlayerUp>
        {
                bool m_state;
        public:
                EventPlayerUp(bool s) :
                        m_state(s)
                {}

                inline bool getState()
                {
                        return m_state;
                }
        };

        class EventPlayerLeft :
                public Event<EventPlayerLeft>
        {
                bool m_state;
        public:
                EventPlayerLeft(bool s) :
                        m_state(s)
                {}

                inline bool getState()
                {
                        return m_state;
                }
        };

        class EventPlayerRight :
                public Event<EventPlayerRight>
        {
                bool m_state;
        public:
                EventPlayerRight(bool s) :
                        m_state(s)
                {}

                inline bool getState()
                {
                        return m_state;
                }
        };
}

#endif //_EVENTS_HPP_
