#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include <vector>

#include "objects.hpp"

namespace Flyy
{

    // using PositionUnit = long long int;
    // using VectorUnit = int;
    typedef long long int PositionUnit;
    typedef int VectorUnit;
    #define P_UNIT_TO_METER 10000

    struct Rectangle
    {
        PositionUnit x;
        PositionUnit y;
        PositionUnit w;
        PositionUnit h;

    };

    struct Position
    {
        PositionUnit x;
        PositionUnit y;
        Position(int px = 0, int py = 0);
        Position& operator=(const Position& p);
    };

    class Vector
    {
        VectorUnit m_x;
        VectorUnit m_y;
    public:
        Vector();
        Vector(VectorUnit magnitude, float angle);
        VectorUnit getX();
        void setX(VectorUnit x);
        VectorUnit getY();
        void setY(VectorUnit y);
        VectorUnit getMagnitude();
        float getAngle();
        float getAngleInRadians();

        Vector& operator+=(Vector v);
        Vector& operator*=(float s);
    };

    Vector operator+(Vector a, Vector b);
    Vector operator*(Vector a, float b);
    Vector operator*(float a, Vector b);

    class PhysicalObject :
        protected Rectangle
    {
    public:
        PhysicalObject(){};
        PhysicalObject(int w, int h);
        PhysicalObject(int w, int h, Position p);
        void setPosition(Position newPosition);
        void updatePosition(Vector v, float t);
        Position getPosition();
        PositionUnit left() const;
        PositionUnit right() const;
        PositionUnit top() const;
        PositionUnit bottom() const;
    };

    class ObjectInWorld :
        public Object
    {
    protected:
        PhysicalObject m_rect;
        float m_coefficientOfElasticity;
    public:
        PhysicalObject getRect() const;
        PositionUnit left() const;
        PositionUnit right() const;
        PositionUnit top() const;
        PositionUnit bottom() const;
        float getCoefficientOfElasticity() const;
    protected:

    };

    class Wall :
        public ObjectInWorld
    {
    public:
        Wall(){};
        Wall(float cOfElasticity, PhysicalObject r);
    };

    class MovableObject :
        public ObjectInWorld
    {
        unsigned m_mass;
        Vector m_velocity;
        float m_coefficientOfResistance;
    public:
        MovableObject(){};
        MovableObject(unsigned mass, float cOfResistance,
                      float cOfElasticity, PhysicalObject r);
        unsigned getMass() const;
        void accelerate(Vector a, float slowdowned);
        Vector getV() const;
        void setV(Vector v);
        void move(PositionUnit dx, PositionUnit dy);
        void setPosition(Position p);
        float getCoefficientOfResistance() const;
        void updatePosition(float slowdowned);
        void backPosition(VectorUnit deltaMagnitude);
        void backPosition(VectorUnit deltaMagnitude, float angle);
    };

    class World
    {
        std::vector<Wall> m_walls;
        std::vector<MovableObject> m_movables;

        float m_coefficientOfSlowdown;

        Vector m_gravityAcceleration;
        float m_coefficientOfResistanceOfEnvironment;
        bool m_hasBeenChanged;
    public:
        World(float cOfEnvResistance = 1,
              float gi = 50);
        void update();
        void setWalls(std::vector<Wall> walls);
        void setMovables(std::vector<MovableObject> movables);
        int add(Wall wall);
        int add(MovableObject movable);
        const std::vector<Wall>& getWalls() const;
        const std::vector<MovableObject>& getMovables() const;
        Wall getWall(int index) const;
        MovableObject getMovable(int index) const;
        void accelerate(int index, Vector a);
        bool hasBeenChanged();
        void changesHasBeenSeen();
        void setCoefficientOfSlowdown(short cOfSlowdown);
        short getCoefficientOfSlowdown();
    private:
        void updatePosition(MovableObject& object);
        Vector getEnvResistanceEffects(const MovableObject& object);
        void objectCollisionDetection(MovableObject& object);
        std::vector<MovableObject> getNearbyObjects(const MovableObject& object);
        std::vector<Wall> getNearbyWalls(const MovableObject& object);
        void calculateCollisionEffects(MovableObject& o1,
                                       MovableObject& o2);
        void calculateCollisionEffects(MovableObject& o, Wall& w);
    };

    class ObjectDriver
    {
        int m_index;
        World* m_world;
    public:
        ObjectDriver(MovableObject movable, World& world);
        MovableObject getObject();
        void accelerate(Vector a);
    };
}

#endif //_WORLD_HPP_
