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

	int getArrivalInSeconds() const { return arrivalHour * 3600 + arrivalMinute * 60; }
	int getDepartureInSeconds() const { return departureHour * 3600 + departureMinute * 60; }
};
