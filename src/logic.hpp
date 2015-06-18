#ifndef _LOGIC_HPP_
#define _LOGIC_HPP_

namespace Flyy
{
    namespace Game
    {
        class Event;    // declared Flyy::Game::Event from event.hpp
        class Control;  // declared Flyy::Game::Control from control.hpp

        class Logic
        {
            Control* m_control;

        public:
            virtual ~Logic() = default;
            virtual void action(const Event* event) = 0;
            virtual void update() = 0;
            void setControl(Control* control);
            Control* control();
        };
    } // namespace Game
} // namespace Flyy

#endif //_LOGIC_HPP_
