#include "frame.hpp"        // Flyy::Gui::Frame
#include "sdl_frame.hpp"    // Flyy::SDL::Frame
#include "exception.hpp"    // Flyy::Exception

#include <iostream>         // std::cout
                            // std::endl

int main(int argc, char** argv)
{
    Flyy::Gui::Frame* game = new Flyy::SDL::Frame(); // Lua TODO
    try {
        game->init();                       // initialising the game
    } catch ( Flyy::Exception e ) {         // catching init exception 
        std::cout << e.what() << std::endl; //// printing what happened
        return 1;                           //// exiting with error
    }
    game->start();                          // starting the game
                                            // waiting for the finish
    game->destroy();                        // destroing the game 
    delete game;                            // deleting the game
    return 0;                               // exiting normal
}

