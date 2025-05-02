#include "Airplane.h"
#include <iostream>

Airplane::Airplane(std::string id, std::unique_ptr<Role> role)
    : id(std::move(id)), role(std::move(role)),
    fuel(role->getInitFuel()),
    circles(role->getMaxCircles()),
    status(AirplaneStatus::waitTakeoff) {}

void Airplane::tick()
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
    //Î×ÈÑÒÊÀ ÏÀÌßÒÈ?
    //ÀÍÈÌÀÖÈß???
}

bool Airplane::requestLanding() //ÂÇÀÈÌÎÄÅÉÑÒÂÈÅ Ñ ÈÃĞÎÊÎÌ
//ÁÓÄÅÌ ÏĞÀÂÈÒÜ ÂÎÇÌÎÆÍÎ 
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