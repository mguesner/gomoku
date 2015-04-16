#include "Input.hpp"

Input::Input()
{
}

Input::Input(eInput input) : input(input)
{
}

Input::Input(eInput input, int x, int y) : input(input), x(x), y(y)
{

}

Input::Input(Input const & src)
{
	(void)src;
}

Input& Input::operator=(Input const & rhs)
{
	(void)rhs;
	return *this;
}

eInput Input::GetType()
{
	return input;
}

int Input::GetX()
{
	return x;
}

int Input::GetY()
{
	return y;
}

Input::~Input()
{
}

