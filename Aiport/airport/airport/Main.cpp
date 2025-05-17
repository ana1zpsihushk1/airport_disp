#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Strip.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Airport Strips");

    std::vector<std::shared_ptr<Strip>> strips;

    // Горизонтальные полосы
    float h_height = 30;
    float h_spacingY = 150;
    float h_y[] = { 150, 300, 450 };
    float h_length[] = { 700, 1000, 700 };
    float h_startX[] = { 250, 100, 250 };

    for (int i = 0; i < 3; ++i)
    {
        auto strip = std::make_shared<Strip>(i, StripType::NarrowbodyOnly); //poka randomnyi type
        strip->setShapeGeometry({ h_length[i], h_height }, { h_startX[i], h_y[i] }, sf::Color(100, 100, 100));
        strips.push_back(strip);
    }

    // Вертикальные полосы
    float v_height = h_spacingY * 2 + h_height;
    float v_width = 30;
    float v_y_start = h_y[0] - 10;
    float v_x[] = { 300, 500, 700 };

    for (int i = 0; i < 3; ++i)
    {
        auto strip = std::make_shared<Strip>(3 + i, StripType::WidebodyOnly);
        strip->setShapeGeometry({ v_width, v_height }, { v_x[i], v_y_start }, sf::Color(80, 80, 80));
        strips.push_back(strip);
    }

    // Дополнительная вертикальная полоса
    auto longStrip = std::make_shared<Strip>(6, StripType::CargoOnly);
    longStrip->setShapeGeometry({ v_width, 600 }, { 950, 100 }, sf::Color(60, 60, 60));
    strips.push_back(longStrip);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color(30, 150, 30)); // фон
        for (const auto& strip : strips)
        {
            strip->draw(window);
        }
        window.display();
    }
    return 0;
}
