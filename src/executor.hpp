#ifndef _EXECUTOR_HPP_
#define _EXECUTOR_HPP_

#include <map>      // std::map

namespace Flyy
{
    namespace Base
    {
        class Event;    // declared Flyy::Base::Event from event.hpp
        class Command;  // declared Flyy::Base::Commnad from command.hpp

        class Executor
        {
            std::map<int, Base::Command*> m_execs;

        public:
            Executor() = default;

            void exec(const Base::Event* event);
            void add(const Base::Event* event, Base::Command* command);
        };
    } // namespace Base
} // namespace Flyy

#endif //_EXECUTOR_HPP_
