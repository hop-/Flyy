#include "sdl_frame.hpp"    // header
#include "exception.hpp"    // Flyy::Exception
#include "game_events.hpp"  // <game events> 
#include "control.hpp"      // Flyy::Base::Control

using namespace Flyy;
using namespace Flyy::SDL;
using namespace Flyy::Base;

Frame::Frame(std::string title, int w, int h) :
    m_width{w},
    m_height{h},
    m_title{title}
{}

void Frame::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw Exception("Frame - Bad init SDL.");
    }
    m_window = SDL_CreateWindow(m_title.c_str(),
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                m_width,
                                m_height,
                                SDL_WINDOW_SHOWN);
    if (m_window == 0) {
        throw Exception("Frame - Bad init window.");
    }
    m_renderer = SDL_CreateRenderer(m_window,
                                    -1,
                                    SDL_RENDERER_ACCELERATED);
    if (m_renderer == 0) {
        throw Exception("Frame - Bad init renderer.");
    }
    m_surface = SDL_CreateRGBSurface(0,
                                     m_width,
                                     m_height,
                                     32,
                                     0, 0, 0, 0);
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
}

void Frame::destroy()
{
    SDL_DestroyRenderer(m_renderer);
    m_renderer = 0;
    SDL_DestroyTexture(m_texture);
    m_texture = 0;
    SDL_FreeSurface(m_surface);
    m_surface = 0;
    SDL_DestroyWindow(m_window);
    m_window = 0;
}

void Frame::draw()
{
    SDL_RenderPresent(m_renderer);
}

const Base::Event* Frame::getEvent(const Base::Control* control)
{
    SDL_Event sdlEvent;
    SDL_PollEvent(&sdlEvent);
    switch (sdlEvent.type) {
    case SDL_QUIT :
        return new Game::EventQuit();
        break;
    case SDL_KEYDOWN :
        return control->event(sdlEvent.key.keysym.scancode, true);
        break;
    case SDL_KEYUP :
        return control->event(sdlEvent.key.keysym.scancode, false);
        break;
    // mouse events TODO
    default:
        break;
    }
    return 0;
}

unsigned Frame::getTicks()
{
    return SDL_GetTicks();
}
