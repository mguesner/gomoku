#include "Point.hpp"

Point::Point() {
}

Point::Point(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
	forbiden[0] = false;
	forbiden[1] = false;
	forbiden[2] = false;
	nb = 0;
}

Point::Point(Point const & src) {
	x = src.x;
	y = src.y;
	z = src.z;
	forbiden[0] = src.forbiden[0];
	forbiden[1] = src.forbiden[1];
	forbiden[2] = src.forbiden[2];
	nb = src.nb;
	// if (forbiden[1] || forbiden[2])
	// 	std::cout << "FORBIDEN" <<std::endl;
}

Point& Point::operator=(Point const & src) {
	x = src.x;
	y = src.y;
	z = src.z;
	nb = src.nb;
	forbiden[0] = src.forbiden[0];
	forbiden[1] = src.forbiden[1];
	forbiden[2] = src.forbiden[2];
	return *this;
}


Point& Point::operator+=(Point const & ref)
{
	x += ref.x;
	y += ref.y;
	z += ref.z;
	return *this;
}

Point& Point::operator-=(Point const & ref)
{
	x -= ref.x;
	y -= ref.y;
	z -= ref.z;
	return *this;
}

Point Point::operator++(int)
{
	nb++;
	return *this;
}

Point Point::operator--(int)
{
	nb--;
	return *this;
}

bool Point::operator==(Point const & ref)
{
	if (ref.x == x && ref.y == y && ref.z == z)
		return true;
	return false;
}

bool Point::operator!=(Point const & ref)
{
	if (ref.x == x && ref.y == y && ref.z == z)
		return false;
	return true;
}

Point& Point::operator+(Point const & ref)
{
	x += ref.x;
	y += ref.y;
	z += ref.z;
	return *this;
}

bool Point::operator<(Point const & ref) const
{
	return (x < ref.x || (x == ref.x && y < ref.y));
}

Point& Point::operator-(Point const & ref)
{
	x -= ref.x;
	y -= ref.y;
	z -= ref.z;
	return *this;
}

Point::~Point() {
}

void Point::Rotation(double anglex, double angley, double anglez)
{
	double radian;
	double tmpx;
	double tmpy;
	double tmpz;
	if (anglez != 0)
	{
		radian = (anglez * M_PI) / 180;
		tmpx = ((x) * cos(radian)) + ((y) * -sin(radian));
		tmpy = ((x) * sin(radian)) + ((y) * cos(radian));
		tmpz = (z);
		x = tmpx;
		y = tmpy;
		z = tmpz;
	}
	if (angley != 0)
	{
		radian = (angley* M_PI) / 180;
		tmpx = ((x) * cos(radian)) + ((z) * sin(radian));
		tmpy = y;
		tmpz = ((x) * -sin(radian)) + ((z) * cos(radian));
		x = tmpx;
		y = tmpy;
		z = tmpz;
	}
	if (anglex != 0)
	{
		radian = (anglex * M_PI) / 180;
		tmpx = ((x) * 1.0);
		tmpy = (y) * cos(radian) + ((z) * -sin(radian));
		tmpz = ((y) * sin(radian)) + ((z) * cos(radian));
		x = tmpx;
		y = tmpy;
		z = tmpz;
	}
}

double	Point::GetPerspectiveX(double distance)
{
	return ( distance * x / (distance + z));
}

double	Point::GetPerspectiveY(double distance)
{
	return (distance * y / (distance + z));
}

void	Point::SetX(double value)
{
	x = value;
}

void	Point::SetY(double value)
{
	y = value;
}

void	Point::SetZ(double value)
{
	z = value;
}

void	Point::UpdateZ(double coef)
{
	z *= coef;
}

void	Point::UpdateX(double coef)
{
	x *= coef;
}

void	Point::UpdateY(double coef)
{
	y *= coef;
}

double	Point::getX() const
{
	return this->x;
}

double	Point::getY() const
{
	return this->y;
}

double	Point::getZ() const
{
	return this->z;
}

int		Point::getNb() const
{
	return nb;
}

std::ostream& operator<<(std::ostream& os, Point& pt)
{
	os << "x : "<<pt.getX() <<" y :" << pt.getY();
	return os;
}

bool	Point::IsForbiden(eState color) const
{
	return forbiden[color];
}

void	Point::Forbiden(eState color, bool state)
{
	forbiden[color] = state;
	// std::cout << (color == WHITE ? "WHITE" : "BLACK") << " state = " << state << std::endl;
}
