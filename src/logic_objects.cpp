#include "logic_objects.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

#ifdef M_PI
#define _PI M_PI
#else
#define _PI 3.14159265358979323846
#endif

using namespace Flyy;

////////////////////////////////////////////////////////////////

Vector::Vector() :
    m_x(0),
    m_y(0)
{}

Vector::Vector(VectorUnit magnitude, float angle) :
    m_x(magnitude * std::cos(angle * _PI / 180)),
    m_y(magnitude * std::sin(angle * _PI / 180))
{}

VectorUnit Vector::getX()
{
    return m_x;
}

void Vector::setX(VectorUnit x)
{
    m_x = x;
}

VectorUnit Vector::getY()
{
    return m_y;
}

void Vector::setY(VectorUnit y)
{
    m_y = y;
}

VectorUnit Vector::getMagnitude()
{
    return std::sqrt(m_x*m_x + m_y*m_y);
}

float Vector::getAngle()
{
    return std::atan2(m_y, m_x) * 180 / _PI;
}

float Vector::getAngleInRadians()
{
    return std::atan2(m_y, m_x);
}

Vector& Vector::operator+=(Vector v)
{
    m_x += v.m_x;
    m_y += v.m_y;
    return *this;
}

Vector Flyy::operator+(Vector a, Vector b)
{
    return a += b;
}

Vector& Vector::operator*=(float s)
{
    m_x *= s;
    m_y *= s;
    return *this;
}

Vector Flyy::operator*(Vector a, float b)
{
    return a *= b;
}

Vector Flyy::operator*(float a, Vector b)
{
    return b *= a;
}

////////////////////////////////////////////////////////////////

PhysicalObject::PhysicalObject(int width, int height,
                               Position position = Position())
{
    m_rect.p = position;
    m_rect.h = height * P_UNIT_TO_METER;
    m_rect.w = width * P_UNIT_TO_METER;
}

void PhysicalObject::setPosition(Position newPosition)
{
    m_rect.p = newPosition;
}

PositionUnit PhysicalObject::left() const
{
    return m_rect.p.x; 
}

PositionUnit PhysicalObject::right() const
{
    return m_rect.p.x + m_rect.w;
}

PositionUnit PhysicalObject::top() const
{
    return m_rect.p.y + m_rect.h;
}

PositionUnit PhysicalObject::bottom() const
{
    return m_rect.p.y;
}

Position PhysicalObject::getPosition()
{
    return m_rect.p;
};

void PhysicalObject::updatePosition(Vector v, float t)
{
    m_rect.p.x += v.getX() * t;
    m_rect.p.y += v.getY() * t;
}

////////////////////////////////////////////////////////////////

PhysicalObject ObjectInWorld::getRect() const
{
    return m_rect;
}

PositionUnit ObjectInWorld::left() const
{
    return m_rect.left();
}

PositionUnit ObjectInWorld::right() const
{
    return m_rect.right();
}

PositionUnit ObjectInWorld::top() const
{
    return m_rect.top();
}

PositionUnit ObjectInWorld::bottom() const
{
    return m_rect.bottom();
}

float ObjectInWorld::getCoefficientOfElasticity() const
{
    return m_coefficientOfElasticity;
}

////////////////////////////////////////////////////////////////

Wall::Wall(float cOfElasticity, PhysicalObject r)
{
    m_coefficientOfElasticity = cOfElasticity;
    m_rect = r;
}

////////////////////////////////////////////////////////////////

MovableObject::MovableObject(unsigned mass, float cOfResistance,
                             float cOfElasticity, PhysicalObject r) :
    m_mass(mass),
    m_coefficientOfResistance(cOfResistance)
{
    m_coefficientOfElasticity = cOfElasticity;
    m_rect = r;
}

unsigned MovableObject::getMass() const
{
    return m_mass;
}

Vector MovableObject::getV() const
{
    return m_velocity;
}

void MovableObject::move(PositionUnit dx, PositionUnit dy)
{
    Position p = m_rect.getPosition();
    p.x += dx;
    p.y += dy;
    m_rect.setPosition(p);
}

void MovableObject::setPosition(Position p)
{
    m_rect.setPosition(p);
}

float MovableObject::getCoefficientOfResistance() const
{
    return m_coefficientOfResistance;
}

void MovableObject::updatePosition(float slowdowned)
{
    m_rect.updatePosition(m_velocity, slowdowned);
}

void MovableObject::backPosition(VectorUnit deltaMagnitude)
{
    m_rect.updatePosition(Vector(deltaMagnitude, m_velocity.getAngle()), 1);
}

void MovableObject::backPosition(VectorUnit deltaMagnitude, float angle)
{
    m_rect.updatePosition(Vector(deltaMagnitude, angle),     1);
}

void MovableObject::accelerate(Vector a , float slowdowned)
{
    m_velocity += a * std::pow(slowdowned, 2);
}

void MovableObject::setV(Vector v)
{
    m_velocity = v; 
}

////////////////////////////////////////////////////////////////


