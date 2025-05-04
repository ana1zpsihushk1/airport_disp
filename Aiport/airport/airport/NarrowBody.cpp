#include <iostream>
#include <memory>

#include "NarrowBody.h"

NarrowBody::NarrowBody(int fuel = 80, int circles = 2)
	: fuel(fuel), circles(circles) {}

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

