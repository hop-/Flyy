#include "menu.hpp"     // header
#include "bullet.hpp"   // Flyy::Game::Bullet
#include "event.hpp"    // Flyy::Game::Event

using namespace Flyy;
using namespace Flyy::Game;

void Menu::action(const Event* event)
{
    // TODO
}

void Menu::update()
{
    // TODO
}

void Menu::addBullet(Bullet* bullet)
{
    // TODO
}

int Menu::current()
{
    return m_current;
}

void Menu::setCurrent(int current)
{
    m_current = current;
}

void Menu::setCyclic(bool state)
{
    m_cyclic = state;
}
