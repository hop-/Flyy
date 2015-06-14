#include "exception.hpp"

using namespace Flyy;

Exception::Exception(std::string reason) :
    m_reason(reason)
{}

const char* Exception::what() const throw()
{
    return m_reason.c_str();
}
