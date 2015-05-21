#include "gui.hpp"      // header

#include "layer.hpp"    // for using Layer class

#include "exception.hpp"   // for using Exception class

using namespace Flyy;
using namespace Gui;

Frame::Frame(std::string title, int w, int h) :
    m_width{w},
    m_height{h},
    m_title{title}
{}

void Frame::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw Exception("Frame - Bad Init.");
    }
    m_window = SDL_CreateWindow(m_title.c_str(),
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                m_width,
                                m_height,
                                SDL_WINDOW_SHOWN);
    if (m_window == 0) {
        throw Exception("Frame - Can't Create Window.");
    }
}

void Frame::push(Layer* layer)
{
    m_LayerStack.push_back(layer);
}

void Frame::pop()
{
    m_LayerStack.pop_back();
}
