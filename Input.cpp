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
	input = src.input;
	x = src.x;
	y = src.y;
}

Input& Input::operator=(Input const & src)
{
	input = src.input;
	x = src.x;
	y = src.y;
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

