#ifndef _FRAME_HPP_
#define _FRAME_HPP_

#include <list>         // std::list
#include <string>       // std::string
#include "layer.hpp"    // Flyy::Gui::Layer
#include "event.hpp"    // Flyy::Game::Event

namespace Flyy
{
    namespace Gui
    {
        class Frame
        {   
            bool m_running;
            std::list<Layer*> m_LayerStack;

        public:
            Frame() = default;
            virtual ~Frame() = default;
            virtual void init() = 0;
            virtual void destroy() = 0;
            void start();
            void stop();
            void push(Layer* layer);
            void pop();
            virtual Game::Event* getEvent() = 0;

        private:
            virtual void draw() = 0;
        };
    } // namespace Gui 
} // namespace Flyy

#endif //_FRAME_HPP_
