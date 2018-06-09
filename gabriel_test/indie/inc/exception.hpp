#ifndef INDIE_EXEPTION_HPP
#define INDIE_EXEPTION_HPP

#include <exception>
#include <string>

class Exception : public std::exception
{
	public:
	Exception(std::string const &) throw();
	~Exception() throw();
	const char *what() const throw();

	private:
	std::string _message;
};

#endif //ARCADE_EXEPTION_HPP
