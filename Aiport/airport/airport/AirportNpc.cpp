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
    for (auto& r : strips)
    {
        r.draw(window);
    }
}

void AirportNpc::initStrip() 
{
    strips.clear();

    float lineHeight = 200.f;
    sf::Vector2f base = shape.getPosition();

    float offsetX1 = base.x + 20;
    float offsetX2 = base.x + 80;

    float topY = base.y;

    Strip universal(StripType::Universal, (int)lineHeight);
    universal.setSize(sf::Vector2f(40, lineHeight));
    universal.setPosition({ offsetX1, topY - lineHeight });

    Strip limitted(StripType::Limitted, (int)lineHeight);
    limitted.setSize(sf::Vector2f(40, lineHeight));
    limitted.setPosition({ offsetX2, topY - lineHeight });

    strips.push_back(universal);
    strips.push_back(limitted);
}