#include "control.hpp"

using namespace Flyy;
using namespace Flyy::Game;

Control::Control(std::map<KeyInput, Event*> controls) :
    m_controls{controls}
{}

const Event* Control::event(KeyInput i, bool press) const
{
    // press release TODO
    return m_controls.at(i);
}

bool Control::add(KeyInput i, Event* e)
{
    //TODO
    return true;
}

std::map<KeyInput, Event*> Control::get() const
{
    return m_controls;
}

void Control::set(std::map<KeyInput, Event*> controls)
{
    m_controls = controls;
}
