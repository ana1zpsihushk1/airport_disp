#pragma once
#include <iostream>
#include <queue>

#include "Airport.h"

class AirportNpc : public Airport
{
public:
	void tick() override;
	void acceptAirplane(std::shared_ptr<Airplane> plane) override;
private:
	std::vector<std::shared_ptr<Airplane>> airplanes;
};