#ifndef _MENU_HPP_
#define _MENU_HPP_

#include <vector>       // std::vector
#include "logic.hpp"    // Flyy::Game::Logic

namespace Flyy
{
    namespace Game
    {
        class Bullet;       // declared Flyy::Game::Bullet from bullet.hpp

        class Menu :
            public Flyy::Game::Logic
        {
            std::vector<Bullet*> m_bullets;
            int m_current;
            bool m_cyclic;

        public:
            void update();

            void addBullet();

            int current();
            void setCurrent();

            void setCyclic(bool state);
        };
    } // namespace Game
} // namespace Flyy

#endif //_MENU_HPP_
