#pragma once
#include <string>

struct FlightSchedule
{
	int arrivalHour;
	int arrivalMinute;

	int departureHour;
	int departureMinute;

	bool arrived = false;
	bool departed = false;

	std::string getArrivalTimeString() const;
	std::string getDepartureTimeString() const;
};
