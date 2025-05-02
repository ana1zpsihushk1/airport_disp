#pragma once

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Airplane;

class Role
{
public:
	virtual std::string getType() const = 0;
	virtual int getInitFuel() const = 0;
	virtual ~Role() = default;
};