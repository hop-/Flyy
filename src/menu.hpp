#ifndef _MENU_HPP_
#define _MENU_HPP_

#include <vector>       // std::vector
#include "logic.hpp"    // Flyy::Base::Logic

namespace Flyy
{
    namespace Game
    {
        class Bullet;       // declared Flyy::Game::Bullet from bullet.hpp
        class Event;        // declared Flyy::Game::Event from event.hpp

        class Menu :
            public Flyy::Base::Logic
        {
            std::vector<Bullet*> m_bullets;
            int m_current;
            bool m_cyclic;

        public:
            Menu();
            void action(const Event* event);
            void update();

            void addBullet(Bullet* bullet);

            int current();
            void setCurrent(int current);

            void setCyclic(bool state);

        private:
            void init();
        };
    } // namespace Game
} // namespace Flyy

#endif //_MENU_HPP_
