#pragma once
#include <memory>

#include "AirportPlayer.h"

class LevelManager
{
public:
	LevelManager(std::shared_ptr<AirportPlayer> airport);
	void upLevel();
	void restartLevel();

	void updateAirportLevel(); //???

	void checkVictory();
	void checkFailure();

	int getLevel() const { return curLevel; };
private:
	int curLevel = 0;
	std::shared_ptr<AirportPlayer> airportPlayer;
};