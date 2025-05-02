#include <iostream>
#include <sstream>

#include "initState.h"
#include "menuState.h"
#include "definitions.h"

initState::initState(GameDataRef data) : _data(data) {}

void initState::Init()
{
	this->_data->assets.LoadTexture("init_Background", BACKGROUND_PNG);
	this->_data->assets.LoadFont("pixelBit_Font", FONT_FOR_MENU);

	_background.setTexture(this->_data->assets.GetTexture("init_Background"));

	_initText.setFont(this->_data->assets.GetFont("pixelBit_Font"));
	_initText.setString("pREss <spAcE> To conTinuE...");
	_initText.setCharacterSize(32);
	_initText.setFillColor(sf::Color(129, 178, 154));

	sf::FloatRect bounds = _initText.getLocalBounds();
	_initText.setOrigin(bounds.width / 2, bounds.height / 2);
	_initText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void initState::HandleInput()
{
	sf::Event event;
	while (this->_data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->_data->window.close();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		{
			_data->machine.AddState(StateRef(new menuState(_data)), true);  // заменяем на menuState
		}
	}
}

void initState::Update(float dt)
{
}

void initState::Draw(float dt)
{
	this->_data->window.clear();

	this->_data->window.draw(_background);
	this->_data->window.draw(_initText);

	this->_data->window.display();
}
