#ifndef VICTORYEXCEPTION_HPP
#define VICTORYEXCEPTION_HPP

#include <exception>
#include "Gomoku.hpp"

class VictoryException : public std::exception
{
public:
	VictoryException();
	VictoryException(eState);
	virtual const char* what() const throw();
private:
	eState color;
};

#endif
