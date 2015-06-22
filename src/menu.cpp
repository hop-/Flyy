#include "menu.hpp"     // header
#include "bullet.hpp"   // Flyy::Game::Bullet
#include "event.hpp"    // Flyy::Game::Event

using namespace Flyy;
using namespace Flyy::Game;


Menu::Menu()
{
    init();
}

void Menu::action(const Event* event)
{
    // TODO
}

void Menu::update()
{}

void Menu::addBullet(Bullet* bullet)
{
    m_bullets.push_back(bullet);
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

void Menu::init()
{
    // TODO
}
