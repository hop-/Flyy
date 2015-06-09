#ifndef _LAYER_HPP_
#define _LAYER_HPP_

namespace Flyy
{
    namespace Game
    {
        class Event;        // declared Flyy::Game::Event from event.hpp
        class Control;  // declared Flyy::Game::Control from control.hpp
    } // namespace Game

    namespace Gui
    {
        class Frame;        // declared Flyy::Gui::Frame from frame.hpp

        class Layer
        {
            static Frame* m_parent;

            Game::Control* m_control;
            
            bool m_stopped{false};
            bool m_inputIsLocked{false};

        public:
            virtual ~Layer() = default;
            Frame* frame();
            void setFrame(Frame* parent);
            bool isStopped();
            void stop(bool state);
            bool inputIsLocked();
            void lockInput(bool state);
            virtual void update(const Game::Event* event);
            virtual void draw() = 0;
            const Game::Control* control() const;
        };
    } // namespace Gui
} // namespace Flyy

#endif //_LAYER_HPP_
