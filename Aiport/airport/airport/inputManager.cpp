#include "inputManager.h"

bool inputManager::IsHovered(const sf::FloatRect& bounds, sf::RenderWindow& window)
{
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	return bounds.contains(mousePos);
}

bool inputManager::IsPressed(const sf::FloatRect& bounds, sf::Mouse::Button button, sf::RenderWindow& window)
{
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	return bounds.contains(mousePos) && sf::Mouse::isButtonPressed(button);
}

bool inputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window)
{
	sf::FloatRect bounds = object.getGlobalBounds();
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	return bounds.contains(mousePos) && sf::Mouse::isButtonPressed(button);
}

sf::Vector2i inputManager::GetMousePosition(sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}
