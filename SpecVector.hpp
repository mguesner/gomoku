#ifndef SPECVECTOR_HPP
#define SPECVECTOR_HPP

#include <vector>
#include "Point.hpp"

class SpecVector : public std::vector<Point>
{
public:
	SpecVector()
	{
		reserve(19 * 19);
		hiddenCheck.reserve(19 * 19);
	}
	SpecVector(const SpecVector& src) : std::vector<Point>(src)
	{
		hiddenCheck = src.hiddenCheck;
	}

	void insert(Point add)
	{
		if (hiddenCheck[(int)add.getY() * 19 + (int)add.getX()])
			return;
		hiddenCheck[(int)add.getY() * 19 + (int)add.getX()]  = 1;
		push_back(add);
	}

	void insert(std::vector<Point>::iterator cur, std::vector<Point>::iterator end)
	{
		while (cur != end)
		{
			if (!hiddenCheck[(int)(*cur).getY() * 19 + (int)(*cur).getX()])
			{
				hiddenCheck[(int)(*cur).getY()* 19 + (int)(*cur).getX()]  = 1;
				push_back((*cur));
			}
			cur++;
		}
	}

	void Init()
	{
		hiddenCheck = std::vector<char>(19 * 19, 0);
	}

private:
	std::vector<char> hiddenCheck;
};

#endif