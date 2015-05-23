#ifndef _SDLFRAME_HPP_
#define _SDLFRAME_HPP_

#include "frame.hpp"      // Flyy::Gui::Frame
#include <SDL2/SDL.h>   // SDL_Window

namespace Flyy
{
    namespace SDL
    {
        class Frame :
            public Flyy::Gui::Frame
        {   
            // geometry
            int m_width;
            int m_height;
            // title
            std::string m_title;
            // SDL
            SDL_Window* m_window;

        public:
            Frame(std::string title = "Flyy", int w = 800, int h = 600);
            void init();
        };
    } // namespace SDLGui 
} // namespace Flyy

#endif //_SDLFRAME_HPP_
