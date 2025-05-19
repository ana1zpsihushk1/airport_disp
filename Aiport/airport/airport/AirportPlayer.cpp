#include "Airport.h"
#include "Airplane.h"
#include "AirportPlayer.h"

void AirportPlayer::tick()
{
    for (auto& plane : airplanes)
        plane->update(sf::seconds(1.f));
}

void AirportPlayer::acceptAirplane(std::shared_ptr<Airplane> plane)
{
    if (hasFreeSlot())
    {
        airplanes.push_back(plane);
    }
    else
    {
        // ñàìîëåò óõîäèòü íà êðóã (äàëåå: íîâûé çàïðîñ/ïàäåíèå/äî NPC)
    }
}

void AirportPlayer::setLevel(int level)
{
    curLevel = level;
    if (level == 6)
    {
        capacity += 10; //ÎÒÊÀËÈÁÐÎÂÀÒÜ 
    }
    else if (level == 11)
    {
        capacity += 15; //ÎÒÊÀËÈÁÐÎÂÀÒÜ
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
    /*window.draw(shape);
    for (auto& r : strips)
    {
        r.draw(window);
    }*/
}

void AirportPlayer::initStrip()
{
    strips.clear();
    Strip universal(StripType::Universal, 100);
    universal.setPosition({ shape.getPosition().x + 20, shape.getPosition().y + shape.getSize().y + 10 });
    Strip limitted(StripType::Limitted, 100);
    limitted.setPosition({ shape.getPosition().x + 80, shape.getPosition().y + shape.getSize().y + 10 });
    strips.push_back(universal);
    strips.push_back(limitted);
}

Strip* AirportPlayer::findSuitableStrip(const std::string& typeName)
{
    for (auto& s : strips)
    {
        if (!s.isAvailable())
            continue;

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

void AirportPlayer::processTakeoff()
{
    //ÇÄÅÑÜ ÁÓÄÅÒ ÏÐÎÂÅÐÊÀ ÐÀÑÏÈÑÀÍÈß è ÎÒÂÅÒ ÄÈÑÏÅÒ×ÅÐÀ
    for (auto& plane : airplanes)
    {
        if (plane->getStatus() != Status::awaitingTakeoff)
        {
            continue;
        }

        Strip* strip = findSuitableStrip(plane->getRoleType());
        if (strip)
        {
            
            plane->assignStrip(std::make_shared<Strip>(*strip));
            strip->reserveUntil(sf::seconds(10));
            plane->takeoff();
        }
    }
}