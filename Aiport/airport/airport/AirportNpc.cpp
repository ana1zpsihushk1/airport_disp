#include "AirportNpc.h"

void AirportNpc::tick()
{
// тут может будет время меняться?
    for (auto& plane : airplanes) 
    {
        plane->tick();
    }
}

void AirportNpc::acceptAirplane(std::shared_ptr<Airplane> plane) 
{
    airplanes.push_back(plane);
}

void AirportNpc::deleteAirplane(const std::string& id)
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

AirportNpc::AirportNpc(sf::Vector2f position, sf::Vector2f size) 
{
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Red);
}

void AirportNpc::draw(sf::RenderWindow& window) 
{
    window.draw(shape);
}