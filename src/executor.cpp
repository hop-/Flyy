#include "executor.hpp" // header
#include "command.hpp"  // Flyy::Base::Command
#include "event.hpp"    // Flyy::Base::Event

using namespace Flyy;
using namespace Flyy::Base;

void Executor::exec(const Base::Event* event)
{
    m_execs.at(event->getType())->exec();
}

void Executor::add(const Base::Event* event, Base::Command* command)
{
    m_execs.insert(std::pair<int, Command*>(event->getType(), command));
}
