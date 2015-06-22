#include "bullet_types.hpp" // header

using namespace Flyy;
using namespace Flyy::Game;

BulletBool::BulletBool() :
    Bullet()
{
    getState();
}

BulletBool::BulletBool(std::string text) :
    Bullet(text)
{
    getState();
}

void BulletBool::enter()
{
    m_state = !m_state;
}

void BulletBool::right()
{
    m_state = true;
}

void BulletBool::left()
{
    m_state = false;
}

std::string BulletBool::text()
{
    if (m_state) {
        return Bullet::text() + "\t" + "ON";
    } else {
        return Bullet::text() + "\t" + "OFF";
    }
}

void BulletBool::getState()
{
    // TODO
}

////////////////////////////////////////////////////////////

BulletInt::BulletInt() :
    Bullet()
{
    getValue();
}

BulletInt::BulletInt(std::string text) :
    Bullet(text)
{
    getValue();
}

void BulletInt::right()
{
    if (++m_value > m_upperRange) {
        m_value = m_upperRange;
    }
}

void BulletInt::left()
{
    if (--m_value < m_lowerRange) {
        m_value = m_lowerRange;
    }
}

std::string BulletInt::text()
{
    return Bullet::text() + "\t" + std::to_string(m_value);
}

void BulletInt::getValue()
{
    // TODO
}

////////////////////////////////////////////////////////////

BulletExec::BulletExec() :
    Bullet()
{}

BulletExec::BulletExec(std::string text) :
    Bullet(text)
{}

void BulletExec::enter()
{
    // TODO
}
