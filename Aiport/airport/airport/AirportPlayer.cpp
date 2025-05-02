#include "AirportPlayer.h"

void AirportPlayer::tick()
{
    for (auto& plane : airplanes) 
    {
        plane->tick();
    }
}

void AirportPlayer::acceptAirplane(std::shared_ptr<Airplane> plane)
{
    if (hasFreeSlot()) 
    {
        airplanes.push_back(plane);
    }
    else 
    {
        // самолет уходить на круг (далее: новый запрос/падение/до NPC)
    }
}

void AirportPlayer::setLevel(int level)
{
    curLevel = level;
    if (level == 6) 
    {
        capacity += 10; //ќ“ јЋ»Ѕ–ќ¬ј“№ 
    }
    else if (level == 11) 
    {
        capacity += 10; //ќ“ јЋ»Ѕ–ќ¬ј“№
    }
}


void AirportPlayer::deleteAirplane(const std::string& id)
{
    auto it = std::remove_if(airplanes.begin(), airplanes.end(),
        [&](const std::shared_ptr<Airplane>& plane) 
        {
            return plane->getId() == id;
        });
    if (it != airplanes.end()) 
    {
        airplanes.erase(it, airplanes.end());
    }
}

AirportPlayer::AirportPlayer(sf::Vector2f position, sf::Vector2f size) 
{
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Blue);
}

void AirportPlayer::draw(sf::RenderWindow& window) 
{
    window.draw(shape);
}