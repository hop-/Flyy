#include "logic.hpp"

using namespace Flyy;
using namespace Flyy::Base;

void Logic::setControl(Base::Control* control)
{
    m_control= control;
}

Base::Control* Logic::control()
{
    return m_control;
}
