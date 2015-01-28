#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include <vector>

#include "objects.hpp"

namespace Flyy
{

        // usint PositionUnit = long long int;
        // usint VectorUnit = int;
        typedef long long int PositionUnit;
        typedef int VectorUnit;

        enum Direction
        {
                Left,
                Right,
                Up,
                Down
        };

        enum Side
        {
                Top,
                Bottom,
                LeftSide,
                RightSide
        };

        struct Position
        {
                PositionUnit x;
                PositionUnit y;
                Position(int px, int py);
                Position(){};
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
                float getAngleRad();

                Vector& operator+=(Vector v);
                Vector& operator*=(float s);
        };

        Vector operator+(Vector a, Vector b);
        Vector operator*(Vector a, float b);
        Vector operator*(float a, Vector b);

        class Rectangle
        {
                Position m_position;
                int m_height;
                int m_width;
        public:
                Rectangle(){};
                Rectangle(int w, int h);
                Rectangle(int w, int h, Position p);
                void setPosition(Position newPosition);
                void updatePosition(Vector v, unsigned t);
                Position getPosition() {return m_position;};
                PositionUnit left() const;
                PositionUnit right() const;
                PositionUnit top() const;
                PositionUnit bottom() const;
        };

        class ObjectInWorld :
                public Object
        {
        protected:
                Rectangle m_rect;
                float m_coefficientOfElasticity;
        public:
                Rectangle getRect() const;
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
                Wall(float cOfElasticity, Rectangle r);
        };

        class MovableObject :
                public ObjectInWorld
        {
                unsigned m_mass;
                Vector m_v0;
                float m_coefficientOfResistance;
        public:
                MovableObject(){};
                MovableObject(unsigned mass, float cOfResistance,
                              float cOfElasticity, Rectangle r);
                unsigned getMass() const;
                void addV(Vector v);
                Vector getV() const;
                void setV(Vector v);
                float getCoefficientOfResistance() const;
                void updatePosition(unsigned dt);
                void backPosition(VectorUnit deltaMagnitude);
        };

        class World
        {
                MovableObject m_player;
                Wall m_finish;
                std::vector<Wall> m_walls;
                std::vector<MovableObject> m_bots;

                unsigned m_dbTimeUnitToMsec;
                unsigned m_ticks;
                unsigned m_deltaTick;
                unsigned m_motion;

                Vector m_g;
                float m_coefficientOfResistanceOfEnvironment;
                bool m_hasBeenChanged;
        public:
                World();
                World(float cOfEnvResistance,
                      unsigned dbTimeUnitToMsec,
                      float gi);
                void start(unsigned ticks);
                void setPlayer(MovableObject player);
                void setWalls(std::vector<Wall> walls);
                void setMovables(std::vector<MovableObject> movables);
                void add(Wall wall);
                void add(MovableObject movable);
                MovableObject getPlayer() const;
                const std::vector<Wall>& getWalls() const;
                const std::vector<MovableObject>& getMovables() const;
                bool hasBeenChanged();
                void changesHasBeenSeen();
                void update(unsigned ticks);
                void playerControl(Direction d);
        private:
                void updatePosition(MovableObject& object);
                short calculateTime(unsigned deltaTicks);
                Vector getEnvResistanceEffects(const MovableObject& object);
                void objectCollisionDetection(MovableObject& object);
                std::vector<MovableObject> getNearbyObjects(const MovableObject& object);
                std::vector<Wall> getNearbyWalls(const MovableObject& object);
                bool detectedCollisionBetweenObjects(const ObjectInWorld& o1, const ObjectInWorld& o2);
                void calculateCollisionEffects(MovableObject& o1,
                                               MovableObject& o2);
                void calculateCollisionEffects(MovableObject& o, Wall& w);
                bool getCollisionSide(const MovableObject& o,
                                      const Wall& w);
        };
}

#endif //_WORLD_HPP_
