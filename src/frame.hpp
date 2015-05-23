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
            virtual void init() = 0;
            void push(Layer* layer);
            void pop();
            virtual ~Frame() = default;
        };
    } // namespace Gui 
} // namespace Flyy

#endif //_FRAME_HPP_
