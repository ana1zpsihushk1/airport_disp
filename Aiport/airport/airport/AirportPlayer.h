#pragma once
#include <iostream>

#include "Airport.h"

class AirportPlayer : public Airport
{
public:
	void tick() override;
	void acceptAirplane(std::shared_ptr<Airplane> plane) override;
private:
	std::vector<std::shared_ptr<Airplane>> airplanes;
};