#pragma once

#include <SFML/Graphics.hpp>

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

	sf::Color baseColor = sf::Color(144, 238, 144);  // light green
	sf::Color hoverColor = sf::Color(0, 100, 0);     // dark green
};