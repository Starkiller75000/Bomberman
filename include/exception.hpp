/*
EPITECH PROJECT, 2018
cpp_indie_studio
File description:
event
*/

#ifndef EXCEPTION_HPP_
# define EXCEPTION_HPP_

#include <iostream>

class Exception : public std::exception
{
public:
	explicit Exception(std::string const &) throw();
	~Exception() throw();
	const char *what() const throw();
private:
	std::string _message;
};

#endif /* EXCEPTION_HPP_ */
