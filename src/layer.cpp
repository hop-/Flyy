#include "layer.hpp"

using namespace Flyy;
using namespace Flyy::Gui;

Frame* Flyy::Gui::Layer::m_parent = 0;

Frame* Layer::frame()
{
    return m_parent;
}

void Layer::setFrame(Frame* parent)
{
    m_parent = parent;
}

bool Layer::isStopped()
{
    return m_stopped;
}

void Layer::stop(bool state)
{
    m_stopped = state;
}

bool Layer::inputIsLocked()
{
    return m_inputIsLocked;
}

void Layer::lockInput(bool state)
{
    m_inputIsLocked = state;
}
