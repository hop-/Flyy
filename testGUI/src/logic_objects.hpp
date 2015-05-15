#ifndef _LOGIC_OBJECTS_HPP_
#define _LOGIC_OBJECTS_HPP_

#include "base_object.hpp"

#include <list>

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
    protected:
        float m_coefficientOfElasticity;
        std::list<PhysicalObject*> m_intersectedObjects;

    public:
        PhysicalObject(){};
        PhysicalObject(int w, int h, Position p);
        PhysicalObject(float cOfElasticity);
        Rectangle getRect() const;
        PositionUnit left() const;
        PositionUnit right() const;
        PositionUnit top() const;
        PositionUnit bottom() const;
        float getCoefficientOfElasticity() const;
        void clearIntersectedObjectList();
        void addIntersectedObject(PhysicalObject* object);
        bool hasBeenIntersectedWith(const PhysicalObject* object) const;
    };

    class Wall :
        virtual public PhysicalObject
    {
    public:
        Wall(){};
        Wall(float cOfElasticity, Rectangle r);
    };

    class MovableObject :
        virtual public PhysicalObject
    {
        unsigned m_mass;
        Vector m_velocity;
        float m_coefficientOfResistance;

    public:
        MovableObject(){};
        MovableObject(unsigned mass, float cOfResistance,
                      float cOfElasticity, Rectangle r);
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
