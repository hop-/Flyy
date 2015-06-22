#ifndef _EVENT_HPP_
#define _EVENT_HPP_

namespace Flyy
{
    namespace Base
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
            virtual int getType() const = 0;
        };

        template <class T>
        class EventCreator :
            public Event
        {
        public:
            static const ID type;
            int getType() const
            {
                return type();
            }
        };

        template<class T>
        const ID EventCreator<T>::type;
    } // namespace Game
} // namespace Flyy

#endif //_EVENT_HPP_
