#ifndef _GAME_EVENTS_HPP_
#define _GAME_EVENTS_HPP_

#include "event.hpp"    // Flyy::Game::Event
                        // Flyy::Game::EventCreator

namespace Flyy
{
    namespace Game
    {
        class EventQuit :
            public EventCreator<EventQuit>
        {};
    } // namespace Game
} // namespace Flyy

#endif //_GAME_EVENTS_HPP_
