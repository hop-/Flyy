#ifndef _BASE_LAYER_HPP_
#define _BASE_LAYER_HPP_

namespace Flyy
{
    namespace Gui
    {
        class Frame;    // defined class Flyy::Gui::Frame from frame.hpp

        class Layer
        {
            static Frame* m_parent;
            
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
        };
    } // namespace Gui
} // namespace Flyy

#endif //_BASE_LAYER_HPP_
