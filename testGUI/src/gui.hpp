#ifndef _GUI_HPP_
#define _GUI_HPP_

#include "world.hpp"
#include "events.hpp"
#include <SDL2/SDL.h>

namespace Flyy
{
        class Gui
        {
                SDL_Window* m_window;
                SDL_Renderer* m_renderer;
                SDL_Texture* m_texture;
                SDL_Surface* m_surface;
        public:
                Gui();
                void init();
                void update(World& world);
                void destroy();
                unsigned getTicks();
                BaseEvent* getEvent();
        private:
                void drawObj(MovableObject* o, int r, int g, int b);
                void drawObj(Wall* o);
        };
}

#endif //_GUI_HPP_
