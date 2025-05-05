#include <cmath>

#include "initState.h"
#include "menuState.h"
#include "definitions.h"

initState::initState(GameDataRef data) : _data(data) {}

void initState::Init()
{
	_data->assets.LoadTexture("init_Background", BACKGROUND_PNG);
	_data->assets.LoadFont("pixelBit_Font", FONT_FOR_MENU);

	_background.setTexture(_data->assets.GetTexture("init_Background"));

	_initText.setFont(_data->assets.GetFont("pixelBit_Font"));
	_initText.setString("Tap SPACE to continue");
	_initText.setCharacterSize(32);
	//_initText.setFillColor(sf::Color(129, 178, 154));
	_initText.setFillColor(sf::Color::White);

	sf::FloatRect bounds = _initText.getLocalBounds();
	_initText.setOrigin(bounds.width / 2, bounds.height / 2);
	_initText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3);
}

void initState::HandleInput()
{
	sf::Event event;
	while (_data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_data->window.close();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::Space)
		{
			_data->machine.AddState(StateRef(new menuState(_data)), true);
		}
	}
}

void initState::Update(float dt)
{
	float time = _timer.getElapsedTime().asSeconds();
	float alpha = 128 + 127 * std::sin(time * 2.f);

	sf::Color color = _initText.getFillColor();
	color.a = static_cast<sf::Uint8>(alpha);
	_initText.setFillColor(color);
}

void initState::Draw(float dt)
{
	this->_data->window.clear();

	this->_data->window.draw(_background);
	this->_data->window.draw(_initText);

	this->_data->window.display();
}
