#ifndef _FRAME_HPP_
#define _FRAME_HPP_

#include <list>         // std::list
#include <string>       // std::string

namespace Flyy
{
    namespace Game
    {
        class Event;         // declared Flyy::Game::Event from event.hpp
    } // namespace Game

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
            virtual Game::Event* getEvent() = 0;
            virtual unsigned getTicks() = 0;
        };
    } // namespace Gui 
} // namespace Flyy

#endif //_FRAME_HPP_
