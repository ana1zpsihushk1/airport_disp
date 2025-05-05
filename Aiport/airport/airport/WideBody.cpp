#include <iostream>
#include <memory>

#include "WideBody.h"

WideBody::WideBody(int fuel, int circles, int minus, float speed)
	: fuel(fuel), circles(circles), minus(minus), speed(speed) {}

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

float WideBody::getSpeed() const
{
	return speed;
}

