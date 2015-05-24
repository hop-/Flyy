#include "frame.hpp"      // header

using namespace Flyy;
using namespace Flyy::Gui;

void Frame::start()
{
    bool isRun = true;

    do {
        for (Layer* layer : m_LayerStack) {
            if (layer->isStopped()) {
                continue;
            }
        }
    } while (isRun);
}

void Frame::push(Layer* layer)
{
    m_LayerStack.push_back(layer);
}

void Frame::pop()
{
    m_LayerStack.pop_back();
}
