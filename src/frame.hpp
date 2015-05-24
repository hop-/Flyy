#ifndef _FRAME_HPP_
#define _FRAME_HPP_

#include <list>         // std::list
#include <string>       // std::string
#include "layer.hpp"    // Flyy::Gui::Layer

namespace Flyy
{
    namespace Gui
    {
        class Frame
        {   
            std::list<Layer*> m_LayerStack;

        public:
            Frame() = default;
            virtual ~Frame() = default;
            virtual void init() = 0;
            virtual void destroy() = 0;
            void start();
            void push(Layer* layer);
            void pop();
        };
    } // namespace Gui 
} // namespace Flyy

#endif //_FRAME_HPP_
