#include "layer.hpp"

using namespace Flyy;
using namespace Flyy::Gui;

Frame* Flyy::Gui::Layer::m_parent = 0;

Frame* Layer::frame()
{
    return m_parent;
}

void Layer::setFrame(Frame* parent)
{
    m_parent = parent;
}
