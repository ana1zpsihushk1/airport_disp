/*#include "AirportNpc.h"

void AirportNpc::tick()
{
    // òóò ìîæåò áóäåò âðåìÿ ìåíÿòüñÿ?
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
    float stripGap = 10.f;

    sf::Vector2f base = shape.getPosition();
    float topY = base.y;

    float offsetX1 = base.x + 20;
    float offsetX2 = base.x + 80;

    Strip universal(StripType::Universal, (int)lineHeight);
    universal.setSize(sf::Vector2f(40, lineHeight));
    universal.setPosition({ offsetX1, topY - lineHeight - stripGap });

    Strip limitted(StripType::Limitted, (int)lineHeight);
    limitted.setSize(sf::Vector2f(40, lineHeight));
    limitted.setPosition({ offsetX2, topY - lineHeight - stripGap });

    strips.push_back(universal);
    strips.push_back(limitted);
}

Strip* AirportNpc::findSuitableStrip(const std::string& typeName)
{
    for (auto& s : strips)
    {
        if (!s.isAvailable())
        {
            continue;
        }
        if (s.getType() == StripType::Universal)
        {
            return &s;
        }
        if ((s.getType() == StripType::Limitted && typeName == "WideBody") || (s.getType() == StripType::Limitted && typeName == "Cargo"))
        {
            return &s;
        }
    }
    return nullptr;
}

void AirportNpc::processTakeoff()
{
    //ÇÄÅÑÜ ÁÓÄÅÒ ÏÐÎÂÅÐÊÀ ÐÀÑÏÈÑÀÍÈß
    for (auto& plane : airplanes)
    {
        if (plane->getStatus() != AirplaneStatus::waitTakeoff)
        {
            continue;
        }

        Strip* strip = findSuitableStrip(plane->getTypeName());
        if (strip)
        {
            if (plane->requestTakingOff())
            {
                plane->startTakeoff(strip);
            }
        }
    }
}*/