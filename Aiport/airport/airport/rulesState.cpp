#include "rulesState.h"
#include "menuState.h"
#include "definitions.h"

rulesState::rulesState(GameDataRef data) : _data(data) {}

void rulesState::Init()
{
	_data->assets.LoadTexture("rules_Background", BACKGROUND_PNG);
	_data->assets.LoadFont("menu_Font", FONT_FOR_MENU);

	_background.setTexture(_data->assets.GetTexture("rules_Background"));

	_rulesTitle.setFont(_data->assets.GetFont("menu_Font"));
	_rulesTitle.setString("RULES:");
	_rulesTitle.setCharacterSize(56);
	_rulesTitle.setFillColor(sf::Color(180, 255, 80));
	_rulesTitle.setPosition(100, 80);

	_rulesText.setFont(_data->assets.GetFont("menu_Font"));
	_rulesText.setString(
		"Play the role of an Airport Dispatcher!\n\n"
		"- Your goal is to manage the airport to avoid aircraft collisions\n during takeoff/landing on the lanes.\n\n"
		"- On the side panel there are schedules of take-offs and landings of airplanes.\n\n"
		"- You can choose the trajectory for the subsequent movement of the airplane.\n\n"
		"- When requesting a landing, you can send the plane on an additional circle,\n but be careful: the fuel may run out, which leads to a crash!\n\n"
		"- If at least one airplane fails to take off or land successfully,\n the game will be lost.\n\n"
		"May the forces be with you!"
	);
	_rulesText.setCharacterSize(36);
	_rulesText.setFillColor(sf::Color(MAIN_BLACK_COLOR));
	_rulesText.setPosition(100, 160);

	backButton = std::make_unique<Button>(
		sf::Vector2f(350, 60),
		sf::Vector2f(100, SCREEN_HEIGHT - 100),
		"BACK TO MENU",
		_data->assets.GetFont("menu_Font")
	);
}

void rulesState::HandleInput()
{
	sf::Event event;
	while (_data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_data->window.close();

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			_data->window.close();

		sf::Vector2i mouse = sf::Mouse::getPosition(_data->window);
		backButton->update(mouse);

		if (event.type == sf::Event::MouseButtonPressed && backButton->isClicked(mouse))
		{
			_data->machine.AddState(StateRef(new menuState(_data)), true);
		}
	}
}

void rulesState::Update(float dt)
{
}

void rulesState::Draw(float dt)
{
	_data->window.clear();
	_data->window.draw(_background);
	_data->window.draw(_rulesText);
	_data->window.draw(_rulesTitle);
	backButton->draw(_data->window);
	_data->window.display();
}
