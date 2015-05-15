#include "gui.hpp"
#include <iostream>

using namespace Flyy;

Gui::Gui()
{}

void Gui::init()
{
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                return;
        }
        m_window = SDL_CreateWindow("test 2D engine",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    900, 900,
                                    SDL_WINDOW_SHOWN);
        if (m_window == NULL) {
                return;
        }
        m_renderer = SDL_CreateRenderer(m_window,
                                        -1,
                                        SDL_RENDERER_ACCELERATED);
        if (m_renderer == NULL) {
                return;
        }
        m_surface = SDL_CreateRGBSurface(0, 900, 900,
                                         32,
                                         0, 0, 0, 0);
        m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
}

void Gui::update(World& world)
{
        if (world.hasBeenChanged()) {
                world.changesHasBeenSeen();
                SDL_RenderClear(m_renderer);
                SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
                //drawObj(world.getPlayer(), 255, 0, 0);
                std::vector<MovableObject*> os = world.getMovables();
                for (int i = 0; i < int(os.size()); ++i) {
                    if (i == 0)
                        drawObj(os[0], 100, 100, 255);
                    else
                        drawObj(os[i], 255, 255, 0);
                }
                std::vector<Wall*> ws = world.getWalls();
                for (int i = 0; i < int(ws.size()); ++i) {
                        drawObj(ws[i]);
                }
                SDL_RenderPresent(m_renderer);
        }
}

inline SDL_Rect getSTDRect(const Rectangle& r) 
{
        SDL_Rect sdlRect;
        sdlRect.x = r.p.x / 2 / P_UNIT_TO_METER;
        sdlRect.y = 899 - (r.p.y / 2 / P_UNIT_TO_METER);
        sdlRect.h = -r.h / 2 / P_UNIT_TO_METER + 2;
        sdlRect.w = r.w / 2 / P_UNIT_TO_METER;
        //std::cout << sdlRect.x << " | " << sdlRect.y << " [" << sdlRect.w << ", " << sdlRect.h << "]" << std::endl;
        return sdlRect;
}

void Gui::drawObj(MovableObject* o, int r, int g, int b)
{
        SDL_SetRenderDrawColor(m_renderer, r, g, b, 255);
        //Flyy::Rectangle m_rect = o->getRect();
        //std::cout << m_rect.w << "||" << m_rect.h << std::endl;
        SDL_Rect sdlRect = getSTDRect(o->getRect());
        //std::cout << sdlRect.w << "|" << sdlRect.h << std::endl;
        SDL_RenderDrawRect(m_renderer, &sdlRect);
}

void Gui::drawObj(Wall* o)
{
        SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
        SDL_Rect sdlRect = getSTDRect(o->getRect());
        //std::cout << sdlRect.x << " | " << sdlRect.y << " [" << sdlRect.w << ", " << sdlRect.h << "]" << std::endl;
        SDL_RenderDrawRect(m_renderer, &sdlRect);
}

void Gui::destroy()
{
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_DestroyTexture(m_texture);
        SDL_FreeSurface(m_surface);
        SDL_Quit();
}

unsigned Gui::getTicks()
{
        return SDL_GetTicks();
}

BaseEvent* Gui::getEvent()
{
        //BaseEvent* gEvent = NULL;
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
                switch (e.type) {
                case SDL_QUIT :
                        return new EventQuit();
                break;
                case SDL_KEYDOWN :
                        switch (e.key.keysym.scancode) {
                        case SDL_SCANCODE_F2 :
                                return new EventReset();
                                break;
                        case SDL_SCANCODE_ESCAPE :
                                return new EventQuit();
                                break;
                        case SDL_SCANCODE_A :
                                return new IncreaseWarpingEvent();
                                break;
                        case SDL_SCANCODE_Z :
                                return new DecreaseWarpingEvent();
                                break;
                        case SDL_SCANCODE_UP :
                                return new EventPlayerUp(true);
                                break;
                        case SDL_SCANCODE_LEFT :
                                return new EventPlayerLeft(true);
                                break;
                        case SDL_SCANCODE_RIGHT :
                                return new EventPlayerRight(true);
                                break;
                        default:
                                break;
                        }
                break;
                case SDL_KEYUP :
                        switch (e.key.keysym.scancode) {
                        case SDL_SCANCODE_UP :
                                return new EventPlayerUp(false);
                                break;
                        case SDL_SCANCODE_LEFT :
                                return new EventPlayerLeft(false);
                                break;
                        case SDL_SCANCODE_RIGHT :
                                return new EventPlayerRight(false);
                                break;
                        default:
                                break;
                        }
                }
        }
        return NULL;
}
