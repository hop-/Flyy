#include "event.hpp"

using namespace Flyy;
using namespace Game;

ID::ID() :
    m_id(++m_count)
{}

int ID::operator()() const
{
    return m_id; 
}

int ID::m_count = 0;

/////////////////////////////////////////////////////////////////

template<class T>
int EventCreator<T>::getType()
{
    return type();
}

template<class T>
const ID EventCreator<T>::type;

/////////////////////////////////////////////////////////////////
