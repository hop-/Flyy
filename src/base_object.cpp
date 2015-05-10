#include "base_object.hpp"


using namespace Flyy;

////////////////////////////////////////////////////////////////

Position::Position(int px, int py) :
    x(px),
    y(py)
{}

Position& Position::operator=(const Position& p)
{
    x = p.x;
    y = p.y;
    return *this;
}

////////////////////////////////////////////////////////////////

Rectangle::Rectangle() :
    p(),
    w(0),
    h(0)
{}

Rectangle::Rectangle(PositionUnit width, PositionUnit height,
                     Position position = Position()) :
    p(position),
    w(width),
    h(height)
{}

////////////////////////////////////////////////////////////////

BaseObject::BaseObject(){}

BaseObject::BaseObject(Rectangle rect)
{
    rect.p.x = rect.p.x * P_UNIT_TO_METER;
    rect.p.y = rect.p.y * P_UNIT_TO_METER;
    rect.h = rect.h * P_UNIT_TO_METER;
    rect.w = rect.w * P_UNIT_TO_METER;
    m_rect = rect;
}

BaseObject::BaseObject(int width, int height,
                       Position position = Position())
{
    m_rect.p.x = position.x * P_UNIT_TO_METER;
    m_rect.p.y = position.y * P_UNIT_TO_METER;
    m_rect.h = height * P_UNIT_TO_METER;
    m_rect.w = width * P_UNIT_TO_METER;
}

BaseObject::~BaseObject(){}

////////////////////////////////////////////////////////////////

