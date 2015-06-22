#include "layer.hpp"

#include "logic.hpp"    // Flyy::Base::Logic

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

void Layer::update(const Base::Event* event)
{
    m_logic->action(event);
    m_logic->update();
}

const Base::Control* Layer::control() const
{
    return m_logic->control();
}
