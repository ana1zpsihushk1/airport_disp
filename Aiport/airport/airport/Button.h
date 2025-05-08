#pragma once

#include <SFML/Graphics.hpp>
#include "definitions.h"

class Button {
public:
	Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, sf::Font& font);

	void draw(sf::RenderWindow& window);
	void update(const sf::Vector2i& mousePos);
	bool isHovered(const sf::Vector2i& mousePos);
	bool isClicked(const sf::Vector2i& mousePos);

private:
	sf::RectangleShape shape;
	sf::Text label;

	sf::Color baseColor = sf::Color(BUTTON_MAIN_COLOR);
	sf::Color hoverColor = sf::Color(BUTTON_HOVER_COLOR);
};