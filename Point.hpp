#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <math.h>
#include <set>

class Point
{
	public:
		Point();
		Point(double x, double y, double z);
		Point(Point const & src);
		Point& operator=(Point const & rhs);
		~Point();

		void	Rotation(double anglex, double angley, double anglez);
		double	GetPerspectiveY(double distance);
		double	GetPerspectiveX(double distance);
		double	getX() const;
		double	getY() const;
		double	getZ() const;

		void	SetX(double value);
		void	SetY(double value);
		void	SetZ(double value);
		void	UpdateX(double coef);
		void	UpdateY(double coef);
		void	UpdateZ(double coef);

		Point& operator+=(Point const & ref);
		Point& operator-=(Point const & ref);
		bool operator<(Point const & ref) const;
		bool operator==(Point const & ref);
		bool operator!=(Point const & ref);
		Point& operator+(Point const & ref);
		Point& operator-(Point const & ref);
	protected:
		bool		black;
		bool		white;
		double		x;
		double		y;
		double		z;
};

std::ostream& operator<<(std::ostream& os, Point& pt);
#endif
