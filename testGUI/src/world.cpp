#include "world.hpp"

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

inline bool areIntersected(const PhysicalObject* o1,
                           const PhysicalObject* o2)
{
    return (o1->left() < o2->right() &&
        o1->right() > o2->left() &&
        o1->bottom() < o2->top() &&
        o1->top() > o2->bottom() && !o1->hasBeenIntersectedWith(o2));
}

inline PositionUnit getIntersectedX(const PhysicalObject* o1, const PhysicalObject* o2)
{
    PositionUnit d1x, d2x;
    d1x = o1->right() - o2->right() < 0 ? 0 : o1->right() - o2->right();
    d2x = o1->left() - o2->left() < 0 ? 0 : o1->left() - o2->left();
    return o1->right() - o2->left() - d1x - d2x;
}

inline PositionUnit getIntersectedY(const PhysicalObject* o1, const PhysicalObject* o2)
{
    PositionUnit d1y, d2y;
    d1y = o1->top() - o2->top() < 0 ? 0 : o1->top() - o2->top();
    d2y = o1->bottom() - o2->bottom() < 0 ? 0 : o1->bottom() - o2->bottom();
    return o1->top() - o2->bottom() - d1y - d2y;
}

inline bool keepObjectInSurface(MovableObject* o1, const PhysicalObject* o2)
{
    PositionUnit stepsBackForX = std::abs(getIntersectedX(o1, o2) /
                std::cos(o1->getV().getAngleInRadians()));
    PositionUnit stepsBackForY = std::abs(getIntersectedY(o1, o2) /
                std::sin(o1->getV().getAngleInRadians()));
    if (stepsBackForX < stepsBackForY) {
        o1->backPosition(-stepsBackForX - 1);
        return true;
    } else {
        o1->backPosition(-stepsBackForY - 1);
        return false;
    }
}

////////////////////////////////////////////////////////////////

World::World(float cOfEnvResistance,
             float gi) :
    m_coefficientOfSlowdown(1),
    m_gravityAcceleration(gi, 270),
    m_coefficientOfResistanceOfEnvironment(cOfEnvResistance),
    m_hasBeenChanged(true)
{}

void World::setWalls(std::vector<Wall*> walls)
{
    m_walls = walls;
}

void World::setMovables(std::vector<MovableObject*> movables)
{
    m_movables = movables;
}

int World::add(Wall* wall)
{
    m_walls.push_back(wall);
    return m_walls.size() - 1 ;
}

int World::add(MovableObject* movable)
{
    m_movables.push_back(movable);
    return m_movables.size() - 1;
}

const std::vector<Wall*>& World::getWalls() const
{
    return m_walls;
}

const std::vector<MovableObject*>& World::getMovables() const
{
    return m_movables;
}

Wall* World::getWall(int index) const
{
    return m_walls[index];
}

MovableObject* World::getMovable(int index) const
{
    return m_movables[index];
}

void World::accelerate(int index, Vector a)
{
    m_movables[index]->accelerate(a, m_coefficientOfSlowdown);
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
    for (auto object : m_movables) {
        object->clearIntersectedObjectList();
    }
    for (auto object : m_walls) {
        object->clearIntersectedObjectList();
    }
    for (auto object : m_movables) {
        updatePosition(object);
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

void World::updatePosition(MovableObject* object)
{
    object->updatePosition(m_coefficientOfSlowdown);
    objectCollisionDetection(object);
    Vector acceleration = m_gravityAcceleration;
    acceleration += getEnvResistanceEffects(object);
    object->accelerate(acceleration, m_coefficientOfSlowdown);
}

Vector World::getEnvResistanceEffects(const MovableObject* object)
{
    VectorUnit f_resistance = object->getV().getMagnitude() *
            object->getCoefficientOfResistance() *
            m_coefficientOfResistanceOfEnvironment / 82;
    return Vector(f_resistance / object->getMass(), object->getV().getAngle() - 180);
}

std::vector<MovableObject*> World::getNearbyObjects(const MovableObject* object)
{
    return m_movables;
}

std::vector<Wall*> World::getNearbyWalls(const MovableObject* object)
{
    return m_walls;
}

void World::objectCollisionDetection(MovableObject* object)
{
    for (auto movable : m_movables) {
        if (object != movable && areIntersected(object, movable)) {
            movable->addIntersectedObject(object);
            object->addIntersectedObject(movable);
            calculateCollisionEffects(object, movable);
        }
    }
    for (auto wall : m_walls) {
        if (areIntersected(object, wall)) {
            wall->addIntersectedObject(object);
            object->addIntersectedObject(wall);
            calculateCollisionEffects(object, wall);
        }
    }
}

void World::calculateCollisionEffects(MovableObject* o1, MovableObject* o2)
{
    keepObjectInSurface(o1, o2);
    float e = (o1->getCoefficientOfElasticity() + o2->getCoefficientOfElasticity()) / 2;
    Vector v1, v2;
    v1.setX((VectorUnit(o1->getMass() * o1->getV().getX()) +
        VectorUnit(o2->getMass() * o2->getV().getX()) +
        VectorUnit(e * o2->getMass() * (o2->getV().getX() - o1->getV().getX()))) /
        VectorUnit(o1->getMass() + o2->getMass()));
    v1.setY((VectorUnit(o1->getMass() * o1->getV().getY()) +
        VectorUnit(o2->getMass() * o2->getV().getY()) +
        VectorUnit(e * o2->getMass() * (o2->getV().getY() - o1->getV().getY()))) /
        VectorUnit((o1->getMass() + o2->getMass())));
    v2.setX((VectorUnit(o1->getMass() * o1->getV().getX()) +
        VectorUnit(o2->getMass() * o2->getV().getX()) +
        VectorUnit(e * o1->getMass() * (o1->getV().getX() - o2->getV().getX()))) /
        VectorUnit((o1->getMass() + o2->getMass())));
    v2.setY((VectorUnit(o1->getMass() * o1->getV().getY()) +
        VectorUnit(o2->getMass() * o2->getV().getY()) +
        VectorUnit(e * o1->getMass() * (o1->getV().getY() - o2->getV().getY()))) /
        VectorUnit(o1->getMass() + o2->getMass()));
    o1->setV(v1);
    o2->setV(v2);
} 


void World::calculateCollisionEffects(MovableObject* o, Wall* w)
{
    float newAngle;
    if (keepObjectInSurface(o, w)) {
        newAngle = 180 - o->getV().getAngle();
    } else {
        newAngle = -o->getV().getAngle();
    }
    float e = (o->getCoefficientOfElasticity() + w->getCoefficientOfElasticity()) / 2;
    float newMagnitude = e * o->getV().getMagnitude();
    o->setV(Vector(newMagnitude, newAngle));
}

////////////////////////////////////////////////////////////////

ObjectDriver::ObjectDriver(MovableObject* movable, World& world) :
    m_movable(movable),
    m_world(&world)
{
    m_index = m_world->add(movable);
}

MovableObject* ObjectDriver::getObject()
{
    return m_movable;
}

void ObjectDriver::accelerate(Vector a)
{
    a *= static_cast<float>(P_UNIT_TO_METER);
    m_world->accelerate(m_index, a);
}
