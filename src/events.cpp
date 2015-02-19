#include "events.hpp"

using namespace Flyy;

ID::ID() :
    m_id(++m_count)
{}

inline int ID::operator()() const
{
    return m_id; 
}

int ID::m_count = 0;

template<class T>
inline int Event<T>::getType()
{
    return type();
}

template<class T>
const ID Event<T>::type;

/////////////////////////////////////////////////////////////////
