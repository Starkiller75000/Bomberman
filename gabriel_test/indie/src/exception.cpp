#include "../inc/exception.hpp"

Exception::Exception(std::string const &message) throw() : _message(message)
{
}

Exception::~Exception() throw()
{
}

const char *Exception::what() const throw()
{
	return (_message.c_str());
}
