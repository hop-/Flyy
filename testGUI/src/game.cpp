#include "game.hpp"
#include "events.hpp"
#include <iostream>

using namespace Flyy;
using namespace Flyy::Physics;

Flyy::Game::Game() :
        m_l(1, 49),
        m_g(),
        m_msPerUpdate(1)
{}

void Flyy::Game::start()
{
        init();
        mainLoop();
        m_g.destroy();
}

void Flyy::Game::init()
{
        setupWorld();
        m_g.init();
}

void Flyy::Game::setupWorld()
{
        MovableObject* o1 = new MovableObject(5, 0.3, 0.8, Rectangle(40, 30, Position(400, 1000)));
        MovableObject* o2 = new MovableObject(5, 0.2, 0.88, Rectangle(30, 40, Position(1000, 1000)));
        MovableObject* o3 = new MovableObject(6, 0.3, 0.82, Rectangle(40, 40, Position(1200, 1200)));
        MovableObject* o4 = new MovableObject(4, 0.49, 0.75, Rectangle(30, 30, Position(1300, 1100)));
        o1->setV(Vector(5000, 0));
        o2->setV(Vector(8000, 180));
        o3->setV(Vector(11000, 120));
        o4->setV(Vector(25000, 180));
        m_l.add(o1);
        m_l.add(o2);
        m_l.add(o3);
        m_l.add(o4);
        m_l.add(new Wall(0.9, Rectangle(1800, 100, Position(0, 0))));
        m_l.add(new Wall(0.9, Rectangle(1800, 100, Position(0, 1700))));
        m_l.add(new Wall(0.9, Rectangle(100, 1800, Position(0, 0))));
        m_l.add(new Wall(0.9, Rectangle(100, 1800, Position(1700, 0))));
        m_l.add(new Wall(0.9, Rectangle(600, 10, Position(400, 700))));
}

void Flyy::Game::mainLoop()
{
        BaseEvent* e;
        unsigned previousTime = m_g.getTicks();
        unsigned lag = 0;
        bool run = true;
        Vector upAcceleration(70, 90);
        bool upa = false;
        Vector leftAcceleration(20, 180);
        bool lefta = false;
        Vector rightAcceleration(20, 0);
        bool righta = false;
        while (run) {
                unsigned currentTime = m_g.getTicks();
                unsigned deltaTime = currentTime - previousTime;
                previousTime = currentTime;
                lag += deltaTime;
                //std::cout << lag << std::endl;
                while (lag >= m_msPerUpdate) {
                        e = m_g.getEvent();
                        if (e != NULL) {
                                if (e->getType() == EventQuit::type()) {
                                        run = false;
                                        break;
                                } else if (e->getType() == EventReset::type()) {
                                        m_l = World();
                                        setupWorld();
                                } else if (e->getType() == IncreaseWarpingEvent::type()) {
                                        std::cout << m_l.getCoefficientOfSlowdown() * 2 << std::endl;
                                        m_l.setCoefficientOfSlowdown(m_l.getCoefficientOfSlowdown() * 2);
                                } else if (e->getType() == DecreaseWarpingEvent::type()) {
                                        std::cout << m_l.getCoefficientOfSlowdown() / 2 << std::endl;
                                        m_l.setCoefficientOfSlowdown(m_l.getCoefficientOfSlowdown() / 2);
                                } else if (e->getType() == EventPlayerUp::type()) {
                                        if (static_cast<EventPlayerUp*>(e)->getState()) {
                                                upa = true;
                                        } else {
                                                upa = false;
                                        }
                                } else if (e->getType() == EventPlayerLeft::type()) {
                                        if (static_cast<EventPlayerLeft*>(e)->getState()) {
                                                lefta = true;
                                        } else {
                                                lefta = false;
                                        }
                                } else if (e->getType() == EventPlayerRight::type()) {
                                        if (static_cast<EventPlayerRight*>(e)->getState()) {
                                                righta = true;
                                        } else {
                                                righta = false;
                                        }
                                }
                                delete e;
                        }
                        lag -= m_msPerUpdate;
                        if (upa) {
                                m_l.accelerate(0, upAcceleration);
                        }
                        if (lefta) {
                                m_l.accelerate(0, leftAcceleration);
                        }
                        if (righta) {
                                m_l.accelerate(0, rightAcceleration);
                        }
                        m_l.update();
                }
                m_g.update(m_l);
        }
}
