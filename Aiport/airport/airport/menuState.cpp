#include <iostream>
#include <sstream>

#include "menuState.h"
#include "rulesState.h"
#include "simulationState.h"
#include "stateMachine.h"
#include "definitions.h"

menuState::menuState(GameDataRef data) : _data(data)
{
}

void menuState::Init()
{
	_data->assets.LoadTexture("menu_Background", BACKGROUND_PNG);
	_data->assets.LoadFont("menu_Font", FONT_FOR_MENU);

	_background.setTexture(_data->assets.GetTexture("menu_Background"));
	_font = _data->assets.GetFont("menu_Font");

	_newGameButton = std::make_unique<Button>(sf::Vector2f(300, 70), sf::Vector2f(100, 200), "НОВАЯ ИГРА", _font);
	_continueButton = std::make_unique<Button>(sf::Vector2f(300, 70), sf::Vector2f(100, 300), "ПРОДОЛЖИТЬ ИГРУ", _font);
	_rulesButton = std::make_unique<Button>(sf::Vector2f(300, 70), sf::Vector2f(100, 400), "ПРАВИЛА", _font);
}

void menuState::HandleInput()
{
	sf::Event event;

	while (_data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed ||
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			_data->window.close();
		}

		sf::Vector2i mousePos = sf::Mouse::getPosition(_data->window);

		_newGameButton->update(mousePos);
		_continueButton->update(mousePos);
		_rulesButton->update(mousePos);

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			if (_newGameButton->isClicked(mousePos)) {
				_data->machine.AddState(StateRef(new simulationState(_data)), false);
			}
			else if (_continueButton->isClicked(mousePos)) {
				// заглушка – можно добавить загрузку состояния
				_data->machine.AddState(StateRef(new simulationState(_data)), false);
			}
			else if (_rulesButton->isClicked(mousePos)) {
				_data->machine.AddState(StateRef(new rulesState(_data)), false);
			}
		}
	}
}

void menuState::Update(float dt)
{
}

void menuState::Draw(float dt)
{
	_data->window.clear();
	_data->window.draw(_background);

	_newGameButton->draw(_data->window);
	_continueButton->draw(_data->window);
	_rulesButton->draw(_data->window);

	_data->window.display();
}
