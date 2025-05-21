#include "Button.h"
#include "definitions.h"

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, sf::Font& font)
{
	shape.setSize(size);
	shape.setPosition(position);
	shape.setFillColor(baseColor);
	shape.setOutlineThickness(3);
	shape.setOutlineColor(hoverColor);

	label.setFont(font);
	label.setString(text);
	label.setCharacterSize(32);
	label.setFillColor(sf::Color(MAIN_BLACK_COLOR));

	sf::FloatRect textBounds = label.getLocalBounds();
	label.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	label.setPosition(position.x + size.x / 2, position.y + size.y / 2);

	if (!clickBuffer.loadFromFile(BUTTON_SOUND_EFFECT)) {
		std::cerr << "[Button] There is no sound: " << BUTTON_SOUND_EFFECT << std::endl;
	}
	else {
		clickSound.setBuffer(clickBuffer);
	}
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(label);
}

void Button::update(const sf::Vector2i& mousePos)
{
	if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		shape.setFillColor(hoverColor);
		label.setFillColor(sf::Color(MAIN_WHITE_COLOR));
	}
	else
	{
		shape.setFillColor(baseColor);
		label.setFillColor(sf::Color(MAIN_BLACK_COLOR));
	}
}

bool Button::isHovered(const sf::Vector2i& mousePos)
{
	return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

bool Button::isClicked(const sf::Vector2i& mousePos)
{
	if (isHovered(mousePos)) {
		clickSound.play();
		return true;
	}

	return isHovered(mousePos);
}

void Button::setColors(const sf::Color& base, const sf::Color& hover)
{
	baseColor = base;
	hoverColor = hover;
	shape.setFillColor(baseColor);
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(hoverColor);
}
