#ifndef _LOGIC_HPP_
#define _LOGIC_HPP_

namespace Flyy
{
    namespace Base
    {
        class Event;    // declared Flyy::Base::Event from event.hpp
        class Control;  // declared Flyy::Base::Control from control.hpp

        class Logic
        {
            Base::Control* m_control;

        public:
            virtual ~Logic() = default;
            virtual void action(const Base::Event* event) = 0;
            virtual void update() = 0;
            void setControl(Base::Control* control);
            Base::Control* control();
        };
    } // namespace Base
} // namespace Flyy

#endif //_LOGIC_HPP_
