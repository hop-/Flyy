#ifndef _SDL_OBJECTS_HPP_
#define _SDL_OBJECTS_HPP_

#include "base_object.hpp"  // Flyy::BaseObject
#include <SDL2/SDL.h>       // SDL_Surface
#include <string>           // std::string

namespace Flyy
{
    namespace SDL
    {
        class DrawableObject :
            virtual public BaseObject
        {
            SDL_Surface* m_surface;

        public:
            void setImage(std::string fileName);
            SDL_Surface* image();
            SDL_Rect rect();
        };
    } // namespace Gui
} // namespace Flyy
#endif //_SDL_OBJECTS_HPP_
