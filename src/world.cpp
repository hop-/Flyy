#include "world.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

#ifdef M_PI
#define _PI M_PI
#else
#define _PI 3.14159265358979323846
#endif

#define M_PER_DBU 1000
using namespace Flyy;

////////////////////////////////////////////////////////////////

Position::Position(int px, int py) :
        x(px * M_PER_DBU),
        y(py * M_PER_DBU)
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

inline float Vector::getAngleRad()
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
        h = height * M_PER_DBU;
        w = width * M_PER_DBU;
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

void PhysicalObject::updatePosition(Vector v, double t)
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
        return m_v0;
}

inline float MovableObject::getCoefficientOfResistance() const
{
        return m_coefficientOfResistance;
}

void MovableObject::updatePosition(double dt)
{
        m_rect.updatePosition(m_v0, dt);
}

void MovableObject::backPosition(VectorUnit deltaMagnitude)
{
        m_rect.updatePosition(Vector(deltaMagnitude, m_v0.getAngle()), 1);
}

inline void MovableObject::addV(Vector v)
{
        m_v0 += v;
}

inline void MovableObject::setV(Vector v)
{
        m_v0 = v; 
}

////////////////////////////////////////////////////////////////

World::World(float cOfEnvResistance,
             unsigned dbTimeUnitToMsec,
             float gi) :
        m_dbTimeUnitToMsec(dbTimeUnitToMsec),
        m_ticks(0),
        m_deltaTick(0),
        m_coefficientOfTimeWarp(1),
        m_g(VectorUnit(gi) * M_PER_DBU * std::pow(float(dbTimeUnitToMsec) / 100, 2), 270),
        m_coefficientOfResistanceOfEnvironment(cOfEnvResistance),
        m_hasBeenChanged(true)
{}

void World::start(unsigned ticks)
{
        m_ticks = ticks;
}

void World::setWalls(std::vector<Wall> walls)
{
        m_walls = walls;
}

void World::setMovables(std::vector<MovableObject> movables)
{
        m_movables = movables;
}

void World::add(Wall wall)
{
        m_walls.push_back(wall);
}

void World::add(MovableObject movable)
{
        m_movables.push_back(movable);
}

const std::vector<Wall>& World::getWalls() const
{
        return m_walls;
}

const std::vector<MovableObject>& World::getMovables() const
{
        return m_movables;
}

bool World::hasBeenChanged()
{
        return m_hasBeenChanged;
}

void World::changesHasBeenSeen()
{
        m_hasBeenChanged = false;
}

void World::update(unsigned deltaTicks)
{
        short t = calculateTime(deltaTicks);
        for (int i = 0; i < t; ++i) {
                m_hasBeenChanged = true;
                for (int i = 0; i < static_cast<int>(m_movables.size()); ++i) {
                        updatePosition(m_movables[i]);
                }
        }
}

void World::setCoefficientOfTimeWarp(short cOfTimeWarp)
{
        if (cOfTimeWarp > 0) {
                m_coefficientOfTimeWarp = 1.0 / cOfTimeWarp;
        }
}

short World::getCoefficientOfTimeWarp()
{
        return 1 / m_coefficientOfTimeWarp;
}

void World::updatePosition(MovableObject& object)
{
        objectCollisionDetection(object);
        object.updatePosition(1);
        Vector a = m_g;
        a += getEnvResistanceEffects(object);
        object.addV(a);
}

inline short World::calculateTime(unsigned ticks)
{
        unsigned deltaTicks = ticks - m_ticks;
        m_ticks = ticks;
        m_deltaTick += deltaTicks;
        short deltaDbTime = (short) m_deltaTick / m_dbTimeUnitToMsec;
        m_deltaTick -= m_dbTimeUnitToMsec * deltaDbTime;
        return deltaDbTime;
}

Vector World::getEnvResistanceEffects(const MovableObject& object)
{
        VectorUnit f_resistance = std::pow(object.getV().getMagnitude(), 2) * object.getCoefficientOfResistance() *
                        m_coefficientOfResistanceOfEnvironment / 2200;
        return Vector(f_resistance / object.getMass() * m_dbTimeUnitToMsec / 100, object.getV().getAngle() - 180);
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
                    detectedCollisionBetweenObjects(object, m_movables[i])) {
                       calculateCollisionEffects(object, m_movables[i]); 
                }
        }
        for (int i = 0; i < static_cast<int>(m_walls.size()); ++i) {
                if (detectedCollisionBetweenObjects(object, m_walls[i])) {
                        calculateCollisionEffects(object, m_walls[i]);
                }
        }
}

inline bool World::detectedCollisionBetweenObjects(const ObjectInWorld& o1,
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

void World::calculateCollisionEffects(MovableObject& o1, MovableObject& o2)
{
        float e = (o1.getCoefficientOfElasticity() + o2.getCoefficientOfElasticity()) / 2;
        PositionUnit stepsBackForX = std::abs(getIntersectedX(o1, o2) /
                                std::cos(o1.getV().getAngleRad()));
        PositionUnit stepsBackForY = std::abs(getIntersectedY(o1, o2) /
                                std::sin(o1.getV().getAngleRad()));
        if (stepsBackForX < stepsBackForY) {
                o1.backPosition(-stepsBackForX);
        } else {
                o1.backPosition(-stepsBackForY);
        }
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
        PositionUnit stepsBackForX = std::abs(getIntersectedX(o, w) /
                                std::cos(o.getV().getAngleRad()));
        PositionUnit stepsBackForY = std::abs(getIntersectedY(o, w) /
                                std::sin(o.getV().getAngleRad()));
        if (stepsBackForX < stepsBackForY) {
                newAngle = 180 - o.getV().getAngle();
                o.backPosition(-stepsBackForX);
        } else {
                newAngle = -o.getV().getAngle();
                o.backPosition(-stepsBackForY);
        }
        float e = (o.getCoefficientOfElasticity() + w.getCoefficientOfElasticity()) / 2;
        float newMagnitude = e * o.getV().getMagnitude();
        o.setV(Vector(newMagnitude, newAngle));
}
