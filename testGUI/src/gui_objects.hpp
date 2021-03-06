#ifndef _GUI_OBJECTS_HPP_
#define _GUI_OBJECTS_HPP_

#include "base_object.hpp"

#include <SDL2/SDL.h>

#include <string>
namespace Flyy
{
    namespace Gui
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
#endif //_GUI_OBJECTS_HPP_
