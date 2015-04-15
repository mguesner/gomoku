#include "Point.hpp"

Point::Point() {
}

Point::Point(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Point::Point(Point const & src) {
	x = src.x;
	y = src.y;
	z = src.z;
}

Point& Point::operator=(Point const & src) {
	x = src.x;
	y = src.y;
	z = src.z;
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

double	Point::getX()
{
	return this->x;
}

double	Point::getY()
{
	return this->y;
}

double	Point::getZ()
{
	return this->z;
}

std::ostream& operator<<(std::ostream& os, Point& pt)
{
	os << "x : "<<pt.getX() <<" y :" << pt.getY();
	return os;
}

