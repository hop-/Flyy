#ifndef _FRAME_HPP_
#define _FRAME_HPP_

#include <list>         // std::list
#include <string>       // std::string

namespace Flyy
{
    namespace Base
    {
        class Event;    // declared Flyy::Base::Event from event.hpp
        class Control;  // declared Flyy::Base::Control from control.hpp
    } // namespace Base

    namespace Gui
    {
        class Layer;        // declared Flyy::Gui::Layer from layer.hpp

        class Frame
        {   
            bool m_running;
            std::list<Layer*> m_LayerStack;
            unsigned m_msPerUpdate{1};

        public:
            Frame() = default;
            virtual ~Frame() = default;
            virtual void init() = 0;
            virtual void destroy() = 0;
            void start();
            void stop();
            void push(Layer* layer);
            void pop();
            unsigned updateRate();
            void setUpdateRate(unsigned perMS);

        private:
            virtual void draw() = 0;
            virtual const Base::Event*
                getEvent(const Base::Control* control) = 0;
            virtual unsigned getTicks() = 0;
        };
    } // namespace Gui 
} // namespace Flyy

#endif //_FRAME_HPP_
