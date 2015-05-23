#ifndef _BASE_COMMAND_HPP_
#define _BASE_COMMAND_HPP_

#include "base_object.hpp"

namespace Flyy
{
    namespace Game
    {
        class Command
        {
        public:
            virtual ~Command() {};
            virtual void  exec(BaseObject* object) = 0;
        };
    } // namespace Game
} // namespace Flyy

#endif //_BASE_COMMAND_HPP_
