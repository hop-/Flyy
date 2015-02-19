#include "world.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

#ifdef M_PI
#define _PI M_PI
#else
#define _PI 3.14159265358979323846
#endif

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

Vector::Vector() :
    m_x(0),
    m_y(0)
{}

Vector::Vector(VectorUnit magnitude, float angle) :
    m_x(magnitude * std::cos(angle * _PI / 180)),
    m_y(magnitude * std::sin(angle * _PI / 180))
{}

inline VectorUnit Vector::getX()
{
    return m_x;
}

inline void Vector::setX(VectorUnit x)
{
    m_x = x;
}

inline VectorUnit Vector::getY()
{
    return m_y;
}

inline void Vector::setY(VectorUnit y)
{
    m_y = y;
}

inline VectorUnit Vector::getMagnitude()
{
    return std::sqrt(m_x*m_x + m_y*m_y);
}

inline float Vector::getAngle()
{
    return std::atan2(m_y, m_x) * 180 / _PI;
}

inline float Vector::getAngleInRadians()
{
    return std::atan2(m_y, m_x);
}

Vector& Vector::operator+=(Vector v)
{
    m_x += v.m_x;
    m_y += v.m_y;
    return *this;
}

inline Vector Flyy::operator+(Vector a, Vector b)
{
    return a += b;
}

Vector& Vector::operator*=(float s)
{
    m_x *= s;
    m_y *= s;
    return *this;
}

inline Vector Flyy::operator*(Vector a, float b)
{
    return a *= b;
}

inline Vector Flyy::operator*(float a, Vector b)
{
    return b *= a;
}

////////////////////////////////////////////////////////////////

PhysicalObject::PhysicalObject(int width, int height,
                               Position p = Position())
{
    x = p.x;
    y = p.y;
    h = height * P_UNIT_TO_METER;
    w = width * P_UNIT_TO_METER;
}

inline void PhysicalObject::setPosition(Position newPosition)
{
    x = newPosition.x;
    y = newPosition.y;
}

inline PositionUnit PhysicalObject::left() const
{
       return x; 
}

inline PositionUnit PhysicalObject::right() const
{
    return x + w;
}

inline PositionUnit PhysicalObject::top() const
{
    return y + h;
}

inline PositionUnit PhysicalObject::bottom() const
{
    return y;
}

Position PhysicalObject::getPosition()
{
    Position p;
    p.x = x;
    p.y = y;
    return p;
};

void PhysicalObject::updatePosition(Vector v, float t)
{
    x += v.getX() * t;
    y += v.getY() * t;
}

////////////////////////////////////////////////////////////////

PhysicalObject ObjectInWorld::getRect() const
{
    return m_rect;
}

inline PositionUnit ObjectInWorld::left() const
{
    return m_rect.left();
}

inline PositionUnit ObjectInWorld::right() const
{
    return m_rect.right();
}

inline PositionUnit ObjectInWorld::top() const
{
    return m_rect.top();
}

inline PositionUnit ObjectInWorld::bottom() const
{
    return m_rect.bottom();
}

inline float ObjectInWorld::getCoefficientOfElasticity() const
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

inline unsigned MovableObject::getMass() const
{
    return m_mass;
}

inline Vector MovableObject::getV() const
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

inline float MovableObject::getCoefficientOfResistance() const
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

inline void MovableObject::accelerate(Vector a , float slowdowned)
{
    m_velocity += a * std::pow(slowdowned, 2);
}

inline void MovableObject::setV(Vector v)
{
    m_velocity = v; 
}

////////////////////////////////////////////////////////////////

inline bool areIntersected(const ObjectInWorld& o1,
                           const ObjectInWorld& o2)
{
    return (o1.left() < o2.right() &&
        o1.right() > o2.left() &&
        o1.bottom() < o2.top() &&
        o1.top() > o2.bottom());
}

inline PositionUnit getIntersectedX(const ObjectInWorld& o1, const ObjectInWorld& o2)
{
    PositionUnit d1x, d2x;
    d1x = o1.right() - o2.right() < 0 ? 0 : o1.right() - o2.right();
    d2x = o1.left() - o2.left() < 0 ? 0 : o1.left() - o2.left();
    return o1.right() - o2.left() - d1x - d2x;
}

inline PositionUnit getIntersectedY(const ObjectInWorld& o1, const ObjectInWorld& o2)
{
    PositionUnit d1y, d2y;
    d1y = o1.top() - o2.top() < 0 ? 0 : o1.top() - o2.top();
    d2y = o1.bottom() - o2.bottom() < 0 ? 0 : o1.bottom() - o2.bottom();
    return o1.top() - o2.bottom() - d1y - d2y;
}

inline bool keepObjectInSurface(MovableObject& o1, const ObjectInWorld& o2)
{
    PositionUnit stepsBackForX = std::abs(getIntersectedX(o1, o2) /
                std::cos(o1.getV().getAngleInRadians()));
    PositionUnit stepsBackForY = std::abs(getIntersectedY(o1, o2) /
                std::sin(o1.getV().getAngleInRadians()));
    if (stepsBackForX < stepsBackForY) {
        o1.backPosition(-stepsBackForX - 1);
        return true;
    } else {
        o1.backPosition(-stepsBackForY - 1);
        return false;
    }
}
/*
inline bool keepObjectInSurface(MovableObject& o1, const ObjectInWorld& o2)
{
    PositionUnit intersectedX = getIntersectedX(o1, o2);
    PositionUnit intersectedY = getIntersectedY(o1, o2);
    PositionUnit stepsBackForX = intersectedX /
                std::cos(o1.getV().getAngleInRadians());
    if (stepsBackForX > 0) {
        intersectedX = 0 - intersectedX;
    }
    PositionUnit stepsBackForY = intersectedY /
                std::sin(o1.getV().getAngleInRadians());
    if (stepsBackForY > 0) {
        intersectedY = 0 - intersectedY;
    }
    if (std::abs(stepsBackForX) < std::abs(stepsBackForY)) {
        o1.backPosition(intersectedX, 0);
        return true;
    } else {
        o1.backPosition(intersectedY, 90);
        return false;
    }
}
*/
////////////////////////////////////////////////////////////////

World::World(float cOfEnvResistance,
             float gi) :
    m_coefficientOfSlowdown(1),
    m_gravityAcceleration(gi, 270),
    m_coefficientOfResistanceOfEnvironment(cOfEnvResistance),
    m_hasBeenChanged(true)
{}

void World::setWalls(std::vector<Wall> walls)
{
    m_walls = walls;
}

void World::setMovables(std::vector<MovableObject> movables)
{
    m_movables = movables;
}

int World::add(Wall wall)
{
    m_walls.push_back(wall);
    return m_walls.size() - 1 ;
}

int World::add(MovableObject movable)
{
    m_movables.push_back(movable);
    return m_movables.size() - 1;
}

const std::vector<Wall>& World::getWalls() const
{
    return m_walls;
}

const std::vector<MovableObject>& World::getMovables() const
{
    return m_movables;
}

Wall World::getWall(int index) const
{
    return m_walls[index];
}

MovableObject World::getMovable(int index) const
{
    return m_movables[index];
}

void World::accelerate(int index, Vector a)
{
    m_movables[index].accelerate(a, m_coefficientOfSlowdown);
}

bool World::hasBeenChanged()
{
    return m_hasBeenChanged;
}

void World::changesHasBeenSeen()
{
    m_hasBeenChanged = false;
}

void World::update()
{
    m_hasBeenChanged = true;
    for (int i = 0; i < static_cast<int>(m_movables.size()); ++i) {
        updatePosition(m_movables[i]);
    }
}

void World::setCoefficientOfSlowdown(short cOfSlowdown)
{
    if (cOfSlowdown > 0 && cOfSlowdown <= 8) {
        m_coefficientOfSlowdown = 1.0 / cOfSlowdown;
    }
}

short World::getCoefficientOfSlowdown()
{
    return 1 / m_coefficientOfSlowdown;
}

void World::updatePosition(MovableObject& object)
{
    object.updatePosition(m_coefficientOfSlowdown);
    objectCollisionDetection(object);
    Vector acceleration = m_gravityAcceleration;
    acceleration += getEnvResistanceEffects(object);
    object.accelerate(acceleration, m_coefficientOfSlowdown);
}

Vector World::getEnvResistanceEffects(const MovableObject& object)
{
    VectorUnit f_resistance = std::pow(object.getV().getMagnitude(), 2) *
            object.getCoefficientOfResistance() *
            m_coefficientOfResistanceOfEnvironment / 820000;
    return Vector(f_resistance / object.getMass(), object.getV().getAngle() - 180);
}

std::vector<MovableObject> World::getNearbyObjects(const MovableObject& object)
{
    return m_movables;
}

std::vector<Wall> World::getNearbyWalls(const MovableObject& object)
{
    return m_walls;
}

void World::objectCollisionDetection(MovableObject& object)
{
    for (int i = 0; i < static_cast<int>(m_movables.size()); ++i) {
        if (&object != &m_movables[i] &&
            areIntersected(object, m_movables[i])) {
               calculateCollisionEffects(object, m_movables[i]); 
        }
    }
    for (int i = 0; i < static_cast<int>(m_walls.size()); ++i) {
        if (areIntersected(object, m_walls[i])) {
            calculateCollisionEffects(object, m_walls[i]);
        }
    }
}

void World::calculateCollisionEffects(MovableObject& o1, MovableObject& o2)
{
    keepObjectInSurface(o1, o2);
    float e = (o1.getCoefficientOfElasticity() + o2.getCoefficientOfElasticity()) / 2;
    Vector v1, v2;
    v1.setX((VectorUnit(o1.getMass() * o1.getV().getX()) +
        VectorUnit(o2.getMass() * o2.getV().getX()) +
        VectorUnit(e * o2.getMass() * (o2.getV().getX() - o1.getV().getX()))) /
        VectorUnit(o1.getMass() + o2.getMass()));
    v1.setY((VectorUnit(o1.getMass() * o1.getV().getY()) +
        VectorUnit(o2.getMass() * o2.getV().getY()) +
        VectorUnit(e * o2.getMass() * (o2.getV().getY() - o1.getV().getY()))) /
        VectorUnit((o1.getMass() + o2.getMass())));
    v2.setX((VectorUnit(o1.getMass() * o1.getV().getX()) +
        VectorUnit(o2.getMass() * o2.getV().getX()) +
        VectorUnit(e * o1.getMass() * (o1.getV().getX() - o2.getV().getX()))) /
        VectorUnit((o1.getMass() + o2.getMass())));
    v2.setY((VectorUnit(o1.getMass() * o1.getV().getY()) +
        VectorUnit(o2.getMass() * o2.getV().getY()) +
        VectorUnit(e * o1.getMass() * (o1.getV().getY() - o2.getV().getY()))) /
        VectorUnit(o1.getMass() + o2.getMass()));
    o1.setV(v1);
    o2.setV(v2);
} 


void World::calculateCollisionEffects(MovableObject& o, Wall& w)
{
    float newAngle;
    if (keepObjectInSurface(o, w)) {
        newAngle = 180 - o.getV().getAngle();
    } else {
        newAngle = -o.getV().getAngle();
    }
    float e = (o.getCoefficientOfElasticity() + w.getCoefficientOfElasticity()) / 2;
    float newMagnitude = e * o.getV().getMagnitude();
    o.setV(Vector(newMagnitude, newAngle));
}

////////////////////////////////////////////////////////////////

ObjectDriver::ObjectDriver(MovableObject movable, World& world) :
    m_world(&world)
{
    m_index = m_world->add(movable);
}

MovableObject ObjectDriver::getObject()
{
    return m_world->getMovable(m_index);
}

void ObjectDriver::accelerate(Vector a)
{
    a *= static_cast<float>(P_UNIT_TO_METER);
    m_world->accelerate(m_index, a);
}
