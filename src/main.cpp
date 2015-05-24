#include "frame.hpp"        // Flyy::Gui::Frame
#include "sdl_frame.hpp"    // Flyy::SDL::Frame

int main(int argc, char** argv)
{
    Flyy::Gui::Frame* game = new Flyy::SDL::Frame(); // Lua TODO
    game->init();
    game->start();
    delete game;
    return 0;
}
