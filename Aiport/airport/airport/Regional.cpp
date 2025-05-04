#include <iostream>
#include <memory>

#include "Regional.h"

Regional::Regional(int fuel = 60, int circles = 2)
	: fuel(fuel), circles(circles) {}

std::string Regional::getType() const
{
	return "Regional";
}

int Regional::getInitFuel() const
{
	return fuel;
}

int Regional::getMaxCircles() const
{
	return circles;
}

