#include "sdl_object.hpp"

#include <SDL2/SDL_image.h>

using namespace Flyy;
using namespace Flyy::SDL;

inline SDL_Rect toSDLRect(const Base::Rectangle& r)
{
    SDL_Rect sdlr;
    sdlr.w = r.w / 2 / P_UNIT_TO_METER;
    sdlr.h = -r.h / 2 / P_UNIT_TO_METER;
    sdlr.x = r.p.x / 2 / P_UNIT_TO_METER;
    sdlr.y = 899 - (r.p.y / 2 / P_UNIT_TO_METER);
    return sdlr;
}

void DrawableObject::setImage(std::string fileName)
{
    m_surface = IMG_Load(fileName.c_str());
}

SDL_Surface* DrawableObject::image()
{
    return m_surface;
}

SDL_Rect DrawableObject::rect()
{
    return toSDLRect(m_rect);
}
