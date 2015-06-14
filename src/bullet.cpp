#include "bullet.hpp"

using namespace Flyy;
using namespace Flyy::Game;

Bullet::Bullet(std::string text) :
    m_text{text}
{}

std::string Bullet::text()
{
    return m_text;
}

void Bullet::setText(std::string text)
{
    m_text = text;
}

bool Bullet::selected()
{
    return m_selected;
}

void Bullet::select(bool state)
{
    m_selected = state;
}
