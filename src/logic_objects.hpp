#ifndef _LOGIC_OBJECTS_HPP_
#define _LOGIC_OBJECTS_HPP_

#include "base_object.hpp"

namespace Flyy
{

    // using VectorUnit = int;
    typedef int VectorUnit;

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
        virtual public BaseObject
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

    class ObjectInWorld
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
}

#endif //_LOGIC_OBJECTS_HPP_
