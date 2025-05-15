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
    // Пример позиции парковки — перед полосами
    sf::Vector2f base = shape.getPosition();
    sf::Vector2f parkPos = base + sf::Vector2f(50.f, -20.f);
    plane->setPosition(parkPos);
    plane->setParkPosition(parkPos); // сохранить позицию парковки
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

    float stripHeight = 200.f;
    float stripGap = 10.f;
    float stripWidth = 40.f;

    sf::Vector2f base = shape.getPosition();
    float bottomY = base.y + shape.getSize().y;

    float offsetX1 = base.x + 20.f;
    float offsetX2 = base.x + 80.f;

    Strip universal(StripType::Universal, (int)stripHeight);
    universal.setSize(sf::Vector2f(stripWidth, stripHeight));
    universal.setPosition({ offsetX1, bottomY + stripGap });

    Strip limitted(StripType::Limitted, (int)stripHeight);
    limitted.setSize(sf::Vector2f(stripWidth, stripHeight));
    limitted.setPosition({ offsetX2, bottomY + stripGap });

    strips.push_back(universal);
    strips.push_back(limitted);
}

Strip* AirportNpc::findSuitableStrip(const std::string& typeName)
{
    for (auto& s : strips)
    {
        if (!s.isAvailable()) continue;
        if (s.getType() == StripType::Universal ||
            (s.getType() == StripType::Limitted && (typeName == "WideBody" || typeName == "Cargo")))
        {
            return &s;
        }
    }
    return nullptr;
}

void AirportNpc::setPlayerAirport(Airport* airport)
{
    playerAirport = airport;
}

void AirportNpc::processTakeoff()
{
    for (auto& plane : airplanes)
    {
        if (plane->getStatus() == AirplaneStatus::waitTakeoff)
        {
            Strip* strip = findSuitableStrip(plane->getTypeName());
            if (strip)
            {
                plane->setDestinationAirport(playerAirport);
                plane->startMoveToStrip(strip);
            }
        }
    }
}