#pragma once
#include "SFML/Graphics.hpp"

class inputManager
{
public:
	inputManager() = default;

	bool IsHovered(const sf::FloatRect& bounds, sf::RenderWindow& window);
	bool IsPressed(const sf::FloatRect& bounds,
		sf::Mouse::Button button, sf::RenderWindow& window);


	bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button,
		sf::RenderWindow& window);
	sf::Vector2i GetMousePosition(sf::RenderWindow& window);
};