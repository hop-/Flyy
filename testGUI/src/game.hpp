#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "world.hpp"
#include "gui.hpp"

namespace Flyy
{
    class Game
    {
        Physics::World m_l;
        Gui m_g;

        unsigned m_msPerUpdate;
    public:
        Game();
        void start();
    private:
        void init();
        void mainLoop();
        void setupWorld();
    };
}

#endif //_GAME_HPP_
