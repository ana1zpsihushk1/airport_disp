#include <iostream>
#include <memory>

#include "WideBody.h"

WideBody::WideBody(int fuel = 100, int circles = 3)
	: fuel(fuel), circles(circles) {}

std::string WideBody::getType() const
{
	return "WideBody";
}

int WideBody::getInitFuel() const
{
	return fuel;
}

int WideBody::getMaxCircles() const
{
	return circles;
}

