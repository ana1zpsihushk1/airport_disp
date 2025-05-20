#pragma once
#include <SFML/System.hpp>
#include <iostream>
#include <string>

#include "definitions.h"

class GameClock
{
public:
	GameClock();

	void update(float dt);
	std::string getTimeString() const;
	int getHour() const;
	int getTotalSeconds() const;

private:
	float _inGameTimeSeconds;
	const float speed = GAME_SPEED;
};