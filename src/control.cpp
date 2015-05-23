#include "control.hpp"

using namespace Flyy;
using namespace Game;

Control::Control(){}

Control::Control(std::map<Input, Command*> controls) :
    m_controls{controls}
{}

void Control::exec(Input i, BaseObject* object)
{
    if (m_controls[i] == 0)
        m_controls[i]->exec(object);
}

bool Control::add(Input i, Command* c)
{
    //TODO
    return true;
}

std::map<Input, Command*> Control::get() const
{
    return m_controls;
}

void Control::set(std::map<Input, Command*> controls)
{
    m_controls = controls;
}
