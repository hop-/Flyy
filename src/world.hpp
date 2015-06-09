#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include <vector>               // std::vector
#include "logic.hpp"            // Flyy::Game::Logic

#include "logic_objects.hpp"    // Flyy::Physics::Wall
                                // Flyy::Physics::MovableObject

namespace Flyy
{
    namespace Physics
    {
        class World :
            public Flyy::Game::Logic
        {
            std::vector<Wall*> m_walls;
            std::vector<MovableObject*> m_movables;

            float m_coefficientOfSlowdown;

            Vector m_gravityAcceleration;
            float m_coefficientOfResistanceOfEnvironment;
            bool m_hasBeenChanged;

        public:
            World(float cOfEnvResistance = 1,
                    float gi = 50);
            void setWalls(std::vector<Wall*> walls);
            void setMovables(std::vector<MovableObject*> movables);
            int add(Wall* wall);
            int add(MovableObject* movable);
            const std::vector<Wall*>& getWalls() const;
            const std::vector<MovableObject*>& getMovables() const;
            Wall* getWall(int index) const;
            MovableObject* getMovable(int index) const;
            void accelerate(int index, Vector a);
            bool hasBeenChanged();
            void changesHasBeenSeen();
            void update();
            void setCoefficientOfSlowdown(short cOfSlowdown);
            short getCoefficientOfSlowdown();

        private:
            void updatePosition(MovableObject* object);
            Vector getEnvResistanceEffects(const MovableObject* object);
            std::vector<MovableObject*> getNearbyObjects(const MovableObject* object);
            void objectCollisionDetection(MovableObject* object);
            std::vector<Wall*> getNearbyWalls(const MovableObject* object);
            void calculateCollisionEffects(MovableObject* o1,
                    MovableObject* o2);
            void calculateCollisionEffects(MovableObject* o, Wall* w);
        };

        class ObjectDriver
        {
            int m_index;
            MovableObject* m_movable;
            World* m_world;

        public:
            ObjectDriver(MovableObject* movable, World& world);
            MovableObject* getObject();
            void accelerate(Vector a);
        };
    } // namespace Physics
 } // namespace Flyy

#endif //_WORLD_HPP_
