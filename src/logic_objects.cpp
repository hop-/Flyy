#include "logic_objects.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

#ifdef M_PI
#define _PI M_PI
#else
#define _PI 3.14159265358979323846
#endif

using namespace Flyy;
using namespace Flyy::Physics;

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

Vector Flyy::Physics::operator+(Vector a, Vector b)
{
    return a += b;
}

Vector& Vector::operator*=(float s)
{
    m_x *= s;
    m_y *= s;
    return *this;
}

Vector Flyy::Physics::operator*(Vector a, float b)
{
    return a *= b;
}

Vector Flyy::Physics::operator*(float a, Vector b)
{
    return b *= a;
}

////////////////////////////////////////////////////////////////

PhysicalObject::PhysicalObject(int width, int height,
                               Position position = Position()) :
    BaseObject(width, height, position)
{}

PhysicalObject::PhysicalObject(float cOfElasticity)
{
    m_coefficientOfElasticity = cOfElasticity;
}

Rectangle PhysicalObject::getRect() const
{
    return m_rect;
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

float PhysicalObject::getCoefficientOfElasticity() const
{
    return m_coefficientOfElasticity;
}

void PhysicalObject::clearIntersectedObjectList()
{
    m_intersectedObjects.clear();
}

void PhysicalObject::addIntersectedObject(PhysicalObject* object)
{
    m_intersectedObjects.push_back(object);
}

bool PhysicalObject::hasBeenIntersectedWith(const PhysicalObject* object) const
{
    for (PhysicalObject* it : m_intersectedObjects) {
        if (it == object) {
            return true;
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////

Wall::Wall(float cOfElasticity, Rectangle r) :
    BaseObject(r),
    PhysicalObject(cOfElasticity)
{}

////////////////////////////////////////////////////////////////

MovableObject::MovableObject(unsigned mass, float cOfResistance,
                             float cOfElasticity, Rectangle r) :
    BaseObject(r),
    PhysicalObject(cOfElasticity)
{
    m_mass = mass;
    m_coefficientOfResistance = cOfResistance;
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
    m_rect.p.x += dx;
    m_rect.p.y += dy;
}

void MovableObject::setPosition(Position p)
{
    m_rect.p = p;
}

float MovableObject::getCoefficientOfResistance() const
{
    return m_coefficientOfResistance;
}

void MovableObject::updatePosition(float slowdowned)
{
    m_rect.p.x += m_velocity.getX() * slowdowned;
    m_rect.p.y += m_velocity.getY() * slowdowned;
}

void MovableObject::backPosition(VectorUnit deltaMagnitude)
{
    Vector backV(deltaMagnitude, m_velocity.getAngle());
    m_rect.p.x += backV.getX();
    m_rect.p.y += backV.getY();
}

void MovableObject::backPosition(VectorUnit deltaMagnitude, float angle)
{
    Vector backV(deltaMagnitude, angle);
    m_rect.p.x += backV.getX();
    m_rect.p.y += backV.getY();
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


