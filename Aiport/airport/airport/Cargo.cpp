#include <iostream>
#include <memory>

#include "Cargo.h"

Cargo::Cargo(int fuel = 100, int circles = 3, int minus = 5)
	: fuel(fuel), circles(circles), minus(minus) {}

std::string Cargo::getType() const
{
	return "Cargo";
}

int Cargo::getInitFuel() const
{
	return fuel;
}

int Cargo::getMaxCircles() const
{
	return circles;
}

int Cargo::getInitMinus() const
{
	return minus;
}