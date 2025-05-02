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
    airplanes.push_back(plane);
    //яюлнкер опхашк б ющпнонпр
    //йнцдю щрн бшгшбюрэ
}
