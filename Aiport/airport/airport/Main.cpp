#include <SFML/Graphics.hpp>

#include <memory>
#include "AirportPlayer.h"
#include "AirportNpc.h"
#include "Strip.h"
#include "Airplane.h"
#include "Role.h"

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
    auto playerAirport = std::make_shared<AirportPlayer>(playerPos, airportSize);
    auto npcAirport = std::make_shared<AirportNpc>(npcPos, airportSize);
    playerAirport->initStrip();
    npcAirport->initStrip();

    std::vector<std::shared_ptr<Airplane>> activePlanes;
    //auto role = std::make_unique<PassengerRole>();  // ПОКА НЕТ ЭТОГО, НО БУДЕТ :)
    //auto plane = std::make_shared<Airplane>("Plane-1", std::move(role));

    //НА СТОЯНКЕ
    //plane->setPosition({ npcPos.x + 100, npcPos.y + 50 });  // немного внутрь прямоугольника
    //activePlanes.push_back(plane);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // обновление логики - ТИК // У МЕНЯ НЕРВНЫЙ ТИК С ЭТИМ ПРОЕКТОМ БУДЕТ
        //playerAirport->tick();
        //npcAirport->tick();

        //for (auto& p : activePlanes)
          //  p->tick();

        // отрисовка Аэропортов и полос
        window.clear(sf::Color::White);
        playerAirport->draw(window);
        npcAirport->draw(window);

        //for (auto& p : activePlanes)
          //  p->draw(window);

        window.display();
    }

	return 0;
}