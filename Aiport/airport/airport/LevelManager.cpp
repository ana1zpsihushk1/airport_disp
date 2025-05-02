#include <iostream>

#include "LevelManager.h"

LevelManager::LevelManager(std::shared_ptr<AirportPlayer> airport)
    : airportPlayer(std::move(airport))
{}

void LevelManager::upLevel()
{
    curLevel++;
    airportPlayer->setLevel(curLevel);
}

void LevelManager::restartLevel()
{
    airportPlayer->setLevel(curLevel);
}


void LevelManager::checkVictory()
{
    if (airportPlayer->getCurLoad() == 0)
    {
        upLevel();
    }
}

void LevelManager::checkFailure()
{
    for (const auto& plane : airportPlayer->getAirplanes())
    {
        if (plane->getStatus() == AirplaneStatus::crashed)
        {
            restartLevel();
            return;
        }
    }
}