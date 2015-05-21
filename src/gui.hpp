#ifndef _GUI_HPP_
#define _GUI_HPP_

#include <list>         // std::list
#include <string>       // std::string
#include <SDL2/SDL.h>   // SDL_window

namespace Flyy
{
    namespace Gui
    {
        class Layer; // declared Layer class from layer.hpp
        
        class Frame
        {   
            // geometry
            int m_width;
            int m_height;
            
            // title
            std::string m_title;

            SDL_Window* m_window;
            std::list<Layer*> m_LayerStack;

        public:
            Frame(std::string title = "Flyy", int w = 800, int h = 600);
            void init();
            void push(Layer* layer);
            void pop();
            virtual ~Frame(){}
        };
    } // namespace Gui 
} // namespace Flyy

#endif //_GUI_HPP_
