/*#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "AirportPlayer.h"
#include "AirportNpc.h"
#include "Strip.h"
#include "Airplane.h"
#include "RoleFabric.h"

int main()
{
    const int windowWidth = 1280;
    const int windowHeight = 720;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Airport Simulation");
    window.setFramerateLimit(60); //или всё-таки 30?

    sf::Vector2f airportSize(300.f, 200.f);
    sf::Vector2f npcPos(20.f, 20.f);
    sf::Vector2f playerPos(windowWidth - airportSize.x - 20.f, 20.f);

    auto airportNpc = std::make_shared<AirportNpc>(npcPos, airportSize);
    auto airportPlayer = std::make_shared<AirportPlayer>(playerPos, airportSize);

    airportNpc->initStrip();
    airportPlayer->initStrip();
    airportNpc->setOppositeAirport(airportPlayer.get());
    airportPlayer->setOppositeAirport(airportNpc.get());
    std::vector<std::shared_ptr<Airplane>> activePlanes;

    // Добавляем самолёт NPC
    auto npcPlane = std::make_shared<Airplane>("NPC_1", createRandomRole());
    npcPlane->setFromNpc(true);
    airportNpc->setPlayerAirport(airportPlayer.get());
    activePlanes.push_back(npcPlane);
    airportNpc->acceptAirplane(npcPlane);

    sf::Clock deltaClock;
    // Игровой цикл
    while (window.isOpen())
    {
        float dt = deltaClock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        airportNpc->processTakeoff(); // проверка на взлёт
        airportNpc->tick(dt);           // движение NPC-самолётов
        airportPlayer->tick(dt);        // игрок пока неактивен

        for (auto& p : activePlanes)
            p->tick(dt);

        window.clear(sf::Color::White);
        airportNpc->draw(window);
        airportPlayer->draw(window);

        for (auto& p : activePlanes)
            p->draw(window);

        window.display();
    }

    return 0;
}*/
