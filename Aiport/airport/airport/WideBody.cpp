#include <iostream>
#include <memory>

#include "WideBody.h"

WideBody::WideBody(int fuel = 100, int circles = 3, int minus = 5)
	: fuel(fuel), circles(circles), minus(minus) {}

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

int WideBody::getInitMinus() const
{
	return minus;
}

