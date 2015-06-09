#ifndef _LOGIC_HPP_
#define _LOGIC_HPP_

namespace Flyy
{
    namespace Game
    {
        class Logic
        {
        public:
            virtual ~Logic() = default;
            virtual void update() = 0;
        };
    } // namespace Game
} // namespace Flyy

#endif //_LOGIC_HPP_
