#ifndef _BASE_COMMAND_HPP_
#define _BASE_COMMAND_HPP_

#include "logic_objects.hpp"

namespace Flyy
{
    namespace Game
    {
        class BaseCommand
        {
        public:
            virtual ~BaseCommand() {};
            virtual void  exec(Physics::PhysicalObject* object) = 0;
        };
    } // namespace Game
} // namespace Flyy

#endif //_BASE_COMMAND_HPP_
