#include "simulationState1.h"
#include "definitions.h"
#include "menuState.h"

simulationState1::simulationState1(GameDataRef data) :_data(data) {}

void simulationState1::Init()
{
	_data->assets.LoadTexture("sim1_Background", BACKGROUND_PNG);
	_data->assets.LoadFont("sim1_Font", FONT_FOR_GAME);

	_background.setTexture(_data->assets.GetTexture("sim1_Background"));

	_label.setFont(_data->assets.GetFont("sim1_Font"));
	_label.setString("Симуляция 1");
	_label.setCharacterSize(40);
	_label.setFillColor(sf::Color::White);

	sf::FloatRect bounds = _label.getLocalBounds();
	_label.setOrigin(bounds.width / 2, bounds.height / 2);
	_label.setPosition(SCREEN_WIDTH / 2, 50);
}

void simulationState1::HandleInput()
{
	sf::Event event;
	while (_data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_data->window.close();

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			_data->machine.AddState(StateRef(new menuState(_data)), true);
		}
	}
}

void simulationState1::Update(float dt) {}

void simulationState1::Draw(float dt)
{
	_data->window.clear();
	_data->window.draw(_background);
	_data->window.draw(_label);
	_data->window.display();
}
