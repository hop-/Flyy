#ifndef _EVENT_HPP_
#define _EVENT_HPP_

namespace Flyy
{
    namespace Game
    {
        class ID
        {
            static int m_count;
            const int m_id;

        public:
            ID();
            int operator()() const;
        };

        class Event
        {
        public:
            virtual ~Event(){};
            virtual int getType() = 0;
        };

        template <class T>
        class EventCreator :
            public Event
        {
        public:
            static const ID type;
            int getType();
        };
    } // namespace Game
} // namespace Flyy

#endif //_EVENT_HPP_
