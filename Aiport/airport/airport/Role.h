#pragma once

#include <iostream>
#include <memory>
#include <vector>

class Airplane;

class Role
{
public:
	virtual std::string getType() const = 0;
	virtual int getInitFuel() const = 0;
	virtual int getMaxCircles() const = 0;
	virtual int getInitMinus() const = 0;
	virtual ~Role() = default;
};