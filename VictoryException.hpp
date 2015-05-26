#ifndef VICTORYEXCEPTION_HPP
#define VICTORYEXCEPTION_HPP

#include <exception>
#include "Gomoku.hpp"

class VictoryException : public std::exception
{
public:
	VictoryException();
	VictoryException(char);
	virtual const char* what() const noexcept;
private:
	char color;
};

#endif
