#ifndef _LOGIC_OBJECTS_HPP_
#define _LOGIC_OBJECTS_HPP_

#include "base_object.hpp"

#include <list>

namespace Flyy
{
    namespace Physics
    {
        using VectorUnit = int;
        // typedef int VectorUnit;

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
            virtual public Base::Object
        {
        protected:
            float m_coefficientOfElasticity;
            std::list<PhysicalObject*> m_intersectedObjects;

        public:
            PhysicalObject(){};
            PhysicalObject(int w, int h, Base::Position p);
            PhysicalObject(float cOfElasticity);
            Base::Rectangle getRect() const;
            Base::PositionUnit left() const;
            Base::PositionUnit right() const;
            Base::PositionUnit top() const;
            Base::PositionUnit bottom() const;
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
            Wall(float cOfElasticity, Base::Rectangle r);
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
                    float cOfElasticity, Base::Rectangle r);
            unsigned getMass() const;
            void accelerate(Vector a, float slowdowned);
            Vector getV() const;
            void setV(Vector v);
            void move(Base::PositionUnit dx, Base::PositionUnit dy);
            void setPosition(Base::Position p);
            float getCoefficientOfResistance() const;
            void updatePosition(float slowdowned);
            void backPosition(VectorUnit deltaMagnitude);
            void backPosition(VectorUnit deltaMagnitude, float angle);
        };
    } // namespace Physics
} // namespace Flyy 

#endif //_LOGIC_OBJECTS_HPP_
