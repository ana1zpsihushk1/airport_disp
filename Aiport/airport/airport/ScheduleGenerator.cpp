#include "ScheduleGenerator.h"
#include <cstdlib>

FlightSchedule generateRandomSchedule()
{
	int depHour = rand() % 24;
	int depMin = (rand() % 4) * 15;  // 00, 15, 30, 45

	int arrOffsetH = 1 + rand() % 5;  // duration of flight
	int arrOffsetM = (rand() % 4) * 15;

	int arrHour = (depHour + arrOffsetH) % 24;
	int arrMin = (depMin + arrOffsetM);

	if (arrMin >= 60)
	{
		arrMin -= 60;
		arrHour = (arrHour + 1) % 24;
	}

	FlightSchedule schedule;

	schedule.arrivalHour = arrHour;
	schedule.arrivalMinute = arrMin;
	schedule.departureHour = depHour;
	schedule.departureMinute = depMin;
	schedule.arrived = false;
	schedule.departed = false;

	return schedule;

}