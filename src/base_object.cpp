#include "base_object.hpp"


using namespace Flyy;

////////////////////////////////////////////////////////////////

Position::Position(int px, int py) :
    x(px * P_UNIT_TO_METER),
    y(py * P_UNIT_TO_METER)
{}

inline Position& Position::operator=(const Position& p)
{
    x = p.x;
    y = p.y;
    return *this;
}

////////////////////////////////////////////////////////////////

BaseObject::BaseObject(){}

BaseObject::BaseObject(PositionUnit width, PositionUnit height,
                       Position position = Position())
{
    m_rect.p = position;
    m_rect.h = height;
    m_rect.w = width;
}

BaseObject::~BaseObject(){}

////////////////////////////////////////////////////////////////

