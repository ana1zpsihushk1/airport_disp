#include <iostream>
#include <memory>

#include "NarrowBody.h"

NarrowBody::NarrowBody(int fuel, int circles, int minus, float speed)
	: fuel(fuel), circles(circles), minus(minus), speed(speed) {
}

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

float NarrowBody::getSpeed() const
{
	return speed;
}