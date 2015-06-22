#ifndef _LAYER_HPP_
#define _LAYER_HPP_

namespace Flyy
{
    namespace Base
    {
        class Event;    // declared Flyy::Base::Event from event.hpp
        class Control;  // declared Flyy::Base::Control from control.hpp
        class Logic;    // declared Flyy::Base::Logic from logic.hpp
    } // namespace Base

    namespace Gui
    {
        class Frame;        // declared Flyy::Gui::Frame from frame.hpp

        class Layer
        {
            static Frame* m_parent;

            Base::Logic* m_logic;
            
            bool m_stopped{false};
            bool m_inputIsLocked{false};

        public:
            virtual ~Layer() = default;
            Frame* frame();
            void setFrame(Frame* parent);
            bool isStopped();
            void stop(bool state);
            bool inputIsLocked();
            void lockInput(bool state);
            void update(const Base::Event* event);
            virtual void draw() = 0;
            const Base::Control* control() const;
        };
    } // namespace Gui
} // namespace Flyy

#endif //_LAYER_HPP_
