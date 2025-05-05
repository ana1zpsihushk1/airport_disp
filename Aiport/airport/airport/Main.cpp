#include <SFML/Graphics.hpp>

#include <memory>
#include <cstdlib>
#include <ctime>

#include "AirportPlayer.h"
#include "AirportNpc.h"
#include "Strip.h"
#include "Airplane.h"
#include "Role.h"
#include "RoleFabric.h"

#include "WideBody.h"
#include "Cargo.h"
#include "NarrowBody.h"
#include "Regional.h"
#include "Local.h"

int main()
{
    const int windowWidth = 1280;
    const int windowHeight = 720;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Airport Game");

    // размеры аэропортов
    sf::Vector2f airportSize(300, 200);

    // позиции
    sf::Vector2f playerPos(windowWidth - airportSize.x - 20, 20);
    sf::Vector2f npcPos(20, windowHeight - airportSize.y - 20);

    // создаём аэропорты
    auto AirPlayer = std::make_shared<AirportPlayer>(playerPos, airportSize);
    auto AirNpc = std::make_shared<AirportNpc>(npcPos, airportSize);
    AirPlayer->initStrip();
    AirNpc->initStrip();

    std::vector<std::shared_ptr<Airplane>> activePlanes;
    int planeId = 0;
    //PLAYER
    auto playerPlane = std::make_shared<Airplane>("Plane_" + std::to_string(planeId++), createRandomRole());
    playerPlane->setPosition({ playerPos.x + 100, playerPos.y + 50 });
    playerPlane->setFromNpc(false);
    activePlanes.push_back(playerPlane);
    AirPlayer->acceptAirplane(playerPlane);

    //NPC
    auto npcPlane = std::make_shared<Airplane>("Plane_" + std::to_string(planeId++), createRandomRole());
    npcPlane->setPosition({ npcPos.x + 100, npcPos.y + 50 });
    npcPlane->setFromNpc(true);
    activePlanes.push_back(npcPlane);
    AirNpc->acceptAirplane(npcPlane);
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // обновление логики - ТИК
        AirPlayer->tick();
        AirNpc->tick();

        AirNpc->processTakeoff();
        AirPlayer->processTakeoff();
        for (auto& p : activePlanes)
        {
            p->tick();
        }
        window.clear(sf::Color::White);
        AirPlayer->draw(window);
        AirNpc->draw(window);

        for (auto& plane : activePlanes)
        {
            plane->draw(window);
        }     
        window.display();
    }
	return 0;
}