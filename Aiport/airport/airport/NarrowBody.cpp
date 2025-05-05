#include <iostream>
#include <memory>

#include "NarrowBody.h"

NarrowBody::NarrowBody(int fuel = 80, int circles = 2, int minus = 4)
	: fuel(fuel), circles(circles), minus(minus) {}

std::string NarrowBody::getType() const
{
	return "NarrowBody";
}

int NarrowBody::getInitFuel() const
{
	return fuel;
}

int NarrowBody::getMaxCircles() const
{
	return circles;
}

int NarrowBody::getInitMinus() const
{
	return minus;
}

