#ifndef _BASE_COMMAND_HPP_
#define _BASE_COMMAND_HPP_

#include "base_object.hpp"

namespace Flyy
{
    namespace Base
    {
        class Command
        {
        public:
            virtual ~Command() {};
            virtual void  exec(Base::Object* object) = 0;
        };
    } // namespace Base
} // namespace Flyy

#endif //_BASE_COMMAND_HPP_
