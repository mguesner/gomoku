#include "VictoryException.hpp"
#include <string>

VictoryException::VictoryException()
{
}

VictoryException::VictoryException(bool color) : color(color)
{
}

const char* VictoryException::what() const noexcept
{
	std::string tmp(color ? "noir" : "blanc");
	tmp.append(" remporte la partie");
	return tmp.c_str();
}
