#ifndef _EXCEPT_HPP_
#define _EXCEPT_HPP_

#include <exception>    // std::exception
#include <string>       // std::string

namespace Flyy
{
    class Exception :
        public std::exception
    {
        std::string m_reason;

    public:
        Exception(std::string reason);
        const char* what() const throw();
    };
} // namespace Flyy

#endif //_EXCEPT_HPP_
