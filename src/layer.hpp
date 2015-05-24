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

        public:
            virtual ~Layer() = default;
            Frame* frame();
            void setFrame(Frame* parent);
        };
    } // namespace Gui
} // namespace Flyy

#endif //_BASE_LAYER_HPP_
