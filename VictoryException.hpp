#ifndef VICTORYEXCEPTION_HPP
#define VICTORYEXCEPTION_HPP

#include <exception>

class VictoryException : public std::exception
{
public:
	VictoryException();
	VictoryException(bool);
	virtual const char* what() const noexcept;
private:
	bool color;
};

#endif
