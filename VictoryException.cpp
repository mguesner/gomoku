#include "VictoryException.hpp"
#include <string>

VictoryException::VictoryException()
{
}

VictoryException::VictoryException(eState color) : color(color)
{
}

const char* VictoryException::what() const noexcept
{
	std::string tmp(color == BLACK ? "noir" : "blanc");
	tmp.append(" remporte la partie");
	return tmp.c_str();
}
