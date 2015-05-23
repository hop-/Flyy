#ifndef _CONTROL_HPP_
#define _CONTROL_HPP_

#include <map>              // std::map

#include "command.hpp" // Flyy::Game::Command

namespace Flyy
{
    namespace Game
    {

        using Input = int;

        class Control
        {
            std::map<Input, Command*>  m_controls;

        public:
            Control();
            Control(std::map<Input, Command*> controls);
            void exec(Input i, BaseObject* object);
            bool add(Input i, Command* c);
            std::map<Input, Command*> get() const;
            void set(std::map<Input, Command*> controls);
        };
    } // namespace Game
} // namespace Flyy

#endif //_CONTROL_HPP_
