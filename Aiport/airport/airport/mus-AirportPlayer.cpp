/*#include "AirportPlayer.h"

void AirportPlayer::tick(float dt)
{
    for (auto& plane : airplanes) 
    {
        plane->tick(dt);
    }
}

//КОПИПАСТ (ЗЛО) С NPC ПОТОМ ПРАВИТЬ БУДЕМ
void AirportPlayer::acceptAirplane(std::shared_ptr<Airplane> plane)
{
    // Пример позиции парковки — перед полосами
    sf::Vector2f base = shape.getPosition();
    sf::Vector2f parkPos = base + sf::Vector2f(50.f, -20.f);
    plane->setPosition(parkPos);
    plane->setParkPosition(parkPos); // сохранить позицию парковки
    airplanes.push_back(plane);
}

void AirportPlayer::setLevel(int level)
{
    curLevel = level;
    if (level == 6) 
    {
        capacity += 10; //ОТКАЛИБРОВАТЬ 
    }
    else if (level == 11) 
    {
        capacity += 10; //ОТКАЛИБРОВАТЬ
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
    for (auto& r : strips)
    {
        r.draw(window);
    }
}

void AirportPlayer::initStrip() 
{
    strips.clear();
    Strip universal(StripType::Universal, 200);
    universal.setPosition({ shape.getPosition().x + 20, shape.getPosition().y + shape.getSize().y + 10 });
    Strip limitted(StripType::Limitted, 200);
    limitted.setPosition({ shape.getPosition().x + 80, shape.getPosition().y + shape.getSize().y + 10 });
    strips.push_back(universal);
    strips.push_back(limitted);
}

Strip* AirportPlayer::findSuitableStrip(const std::string& typeName)
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

//Логика для игрока 
/*void AirportPlayer::processTakeoff()
{
    for (auto& plane : airplanes)
    {
        if (plane->getStatus() == AirplaneStatus::waitTakeoff)
        {
            Strip* strip = findSuitableStrip(plane->getTypeName());
            if (strip)
            {
                plane->startMoveToStrip(strip);
            }
        }
    }
}*/

