#include "logic.hpp"

using namespace Flyy;
using namespace Flyy::Game;

void Logic::setControl(Control* control)
{
    m_control= control;
}

Control* Logic::control()
{
    return m_control;
}
