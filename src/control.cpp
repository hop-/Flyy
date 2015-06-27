#include "control.hpp"

using namespace Flyy;
using namespace Flyy::Base;

Control::Control(std::map<KeyInput, Event*> controls) :
    m_controls{controls}
{}

const Event* Control::event(KeyInput i, bool press) const
{
    // press release TODO
    return m_controls.at(i);
}

void Control::add(KeyInput i, Event* e)
{
    m_controls.insert(std::pair<KeyInput, Event*>(i, e));
}

std::map<KeyInput, Event*> Control::get() const
{
    return m_controls;
}

void Control::set(std::map<KeyInput, Event*> controls)
{
    m_controls = controls;
}
