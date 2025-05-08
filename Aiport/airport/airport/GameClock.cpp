#include <iomanip>
#include <sstream>

#include "GameClock.h"

GameClock::GameClock() : _inGameTimeSeconds(0.f) {}

void GameClock::update(float dt)
{
	_inGameTimeSeconds += dt * speed;
	if (_inGameTimeSeconds >= 86400)
		_inGameTimeSeconds = 0;
}

std::string GameClock::getTimeString() const
{
	int hours = static_cast<int>(_inGameTimeSeconds) / 3600;
	int minutes = (static_cast<int>(_inGameTimeSeconds) % 3600) / 60;

	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << hours << ":"
		<< std::setw(2) << std::setfill('0') << minutes;

	return oss.str();
}

int GameClock::getHour() const
{
	return static_cast<int>(_inGameTimeSeconds) / 3600;
}


