#ifndef _SDLFRAME_HPP_
#define _SDLFRAME_HPP_

#include "frame.hpp"    // Flyy::Gui::Frame
#include <SDL2/SDL.h>   // SDL_Window,
                        // SDL_Renderer,
                        // SDL_Texture,
                        // SDL_Surface

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
            SDL_Renderer* m_renderer;
            SDL_Texture* m_texture;
            SDL_Surface* m_surface;

        public:
            Frame(std::string title = "Flyy", int w = 800, int h = 600);
            ~Frame();
            void init();
            void destroy();
        };
    } // namespace SDLGui 
} // namespace Flyy

#endif //_SDLFRAME_HPP_
