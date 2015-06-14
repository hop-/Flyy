#ifndef _BULLET_HPP_
#define _BULLET_HPP_

#include <string>           // std::string
#include "base_object.hpp"  // Flyy::Base::Object

namespace Flyy
{
    namespace Game
    {
        class Bullet :
            public Base::Object
        {
            std::string m_text;
            bool m_selected;

        public:
            Bullet() = default;
            Bullet(std::string text);
            virtual ~Bullet() = default;

            // virtual void enter() = 0;
            // virtual void left() = 0;
            // virtual void right() = 0;

            virtual std::string text();
            void setText(std::string text);

            bool selected();
            void select(bool state);
        };
    } // namespace Game
} // namespace Flyy

#endif //_BULLET_HPP_
