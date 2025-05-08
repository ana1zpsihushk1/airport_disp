#include <sstream>
#include <iomanip>

#include "FlightSchedule.h"

std::string FlightSchedule::getArrivalTimeString() const
{
	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << arrivalHour << ":"
		<< std::setw(2) << std::setfill('0') << arrivalMinute;
	return oss.str();
}

std::string FlightSchedule::getDepartureTimeString() const
{
	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << departureHour << ":"
		<< std::setw(2) << std::setfill('0') << departureMinute;
	return oss.str();
}
