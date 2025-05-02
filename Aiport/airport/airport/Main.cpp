#include <SFML/Graphics.hpp>

#include <memory>
#include "AirportPlayer.h"
#include "AirportNpc.h"
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

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // обновление логики
        playerAirport->tick();
        npcAirport->tick();

        // отрисовка
        window.clear(sf::Color::White);
        playerAirport->draw(window);
        npcAirport->draw(window);
        window.display();
    }
	return 0;
}