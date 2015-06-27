#include "logic.hpp"
#include "executor.hpp" // Flyy::Base::Executor

using namespace Flyy;
using namespace Flyy::Base;

void Logic::action(const Base::Event* event)
{
    m_executor->exec(event);
}

void Logic::setControl(Base::Control* control)
{
    m_control= control;
}

Base::Control* Logic::control()
{
    return m_control;
}
