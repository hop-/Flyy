#ifndef _CONTROL_HPP_
#define _CONTROL_HPP_

#include <map>          // std::map
#include "event.hpp"    // Flyy::Event

namespace Flyy
{
    namespace Base
    {

        using KeyInput = int;

        class Control
        {
            std::map<KeyInput, Event*>  m_controls;

        public:
            Control() = default;
            Control(std::map<KeyInput, Event*> controls);
            const Event* event(KeyInput i, bool press) const;
            bool add(KeyInput i, Event* e);
            std::map<KeyInput, Event*> get() const;
            void set(std::map<KeyInput, Event*> controls);
        };
    } // namespace Base
} // namespace Flyy

#endif //_CONTROL_HPP_
