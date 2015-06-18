#include "frame.hpp"    // header
#include "layer.hpp"    // Flyy::Gui::Layer
#include "event.hpp"    // Flyy::Game::Event

using namespace Flyy;
using namespace Flyy::Gui;

void Frame::start()
{
    m_running = true;
    unsigned previousTicks = getTicks();
    unsigned realLag = 0;
    // main loop
    do {
        unsigned currentTicks = getTicks();
        unsigned deltaTicks = currentTicks - previousTicks;
        previousTicks = currentTicks;
        realLag += deltaTicks;
        unsigned lag = realLag;     // setted to realLag in case,
                                    // when 'for' loop is empty
        for (Layer* layer : m_LayerStack) {
            const Game::Event* event = getEvent(layer->control());
            if (layer->isStopped()) {
                continue;
            }
            lag = realLag;
            while (lag >= m_msPerUpdate) {
                layer->update(event);
                lag -= m_msPerUpdate;
            }
            layer->draw();
        }
        realLag = lag;
        // delete event; not needed
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

unsigned Frame::updateRate()
{
    return m_msPerUpdate;
}

void Frame::setUpdateRate(unsigned perMS)
{
    m_msPerUpdate = perMS;
}
