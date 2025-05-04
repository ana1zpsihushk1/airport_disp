#include <iostream>
#include "Airplane.h"


Airplane::Airplane(std::string id, std::unique_ptr<Role> role)
    : id(std::move(id)), role(std::move(role)),
    fuel(role->getInitFuel()),
    circles(role->getMaxCircles()),
    status(AirplaneStatus::waitTakeoff) 
{
    sprite.setRadius(10.f);
    sprite.setFillColor(sf::Color::Black); //ïîòîì öâåòà ìåíÿòü áóäåì
    sprite.setOrigin(10.f, 10.f); // öåíòğ êğóãà
}

void Airplane::tick() //åñëè íàäî - ïîïğàâèì
{
    if ((status == AirplaneStatus::inSky) || (status == AirplaneStatus::takingOff)
        || (status == AirplaneStatus::landing))
    {
        fuel--;
        if (fuel <= 0)
        {
            crash();
        }
    }
}

void Airplane::crash()
{
    status = AirplaneStatus::crashed;
    //ÀÍÈÌÀÖÈß???
}

bool Airplane::requestLanding() //ÂÇÀÈÌÎÄÅÉÑÒÂÈÅ Ñ ÈÃĞÎÊÎÌ
//ÁÓÄÅÌ ÏĞÀÂÈÒÜ 
{
    if (circles > 0) 
    {
        circles--;
        return false;
    }
    else 
    {
        status = AirplaneStatus::landing;
        return true;
    }
}

bool Airplane::requestTakingOff() 
{
    //ÒÓÒ ÁÓÄÅÒ ÏĞÎÂÅĞÊÀ ÍÀ ĞÀÑÏÈÑÀÍÈÅ È ÎÒÂÅÒ ÄÅÑÏÅÒ×ÅĞÀ  
    if (status == AirplaneStatus::waitTakeoff)
    {
        status = AirplaneStatus::takingOff;
        return true;
    }
    return false;
}

//îòğèñîâêà
void Airplane::setPosition(sf::Vector2f pos) 
{
    sprite.setPosition(pos);
}

void Airplane::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}