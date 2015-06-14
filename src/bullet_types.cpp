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
    Bullet()
{
    getValue();
}

std::string BulletInt::text()
{
    return Bullet::text() + "\t" + std::to_string(m_value);
}

void BulletInt::getValue()
{
    // TODO
}
