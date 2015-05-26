#include "frame.hpp"      // header

using namespace Flyy;
using namespace Flyy::Gui;

void Frame::start()
{
    m_running = true;
    // main loop
    do {
        for (Layer* layer : m_LayerStack) {
            if (layer->isStopped()) {
                continue;
            }
        }
        draw();
    } while (m_running);
}

void Frame::stop()
{
    m_running = false;
}

void Frame::push(Layer* layer)
{
    m_LayerStack.push_back(layer);
}

void Frame::pop()
{
    m_LayerStack.pop_back();
}
