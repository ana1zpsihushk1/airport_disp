#include "rulesState.h"
#include "menuState.h"
#include "definitions.h"

rulesState::rulesState(GameDataRef data) : _data(data) {}

void rulesState::Init()
{
	//_data->assets.LoadTexture("rules_Background", BACKGROUND_PNG);
	//_data->assets.LoadFont("pixelBit_Font", FONT_FOR_MENU);

	//_background.setTexture(_data->assets.GetTexture("rules_Background"));

	// Настройка текста правил
	//_rulesText.setFont(_data->assets.GetFont("pixelBit_Font"));
	//_rulesText.setString("ПРАВИЛА:\n- Управляй самолётами\n- Не допускай столкновений\n- Следи за топливом\n\nНажми 'Назад' чтобы вернуться");
	//_rulesText.setCharacterSize(36);
	//_rulesText.setFillColor(sf::Color::Color(244, 241, 222));
	//_rulesText.setPosition(50, 100);

	//_backText.setFont(_data->assets.GetFont("pixelBit_Font"));
	//_backText.setString("НАЗАД");
	//_backText.setCharacterSize(50);
	//_backText.setFillColor(sf::Color::Color(244, 241, 222));
	//_backText.setPosition(65, 500);
	
	/*_data->assets.LoadTexture("rules_Background", BACKGROUND_PNG);
	_data->assets.LoadFont("menu_Font", FONT_FOR_MENU);

	_background.setTexture(_data->assets.GetTexture("rules_Background"));

	// Текст с правилами
	_rulesText.setFont(_data->assets.GetFont("menu_Font"));
	_rulesText.setString("ПРАВИЛА:\n"
		"- Управляй самолётами, следи за топливом\n"
		"- Не допускай задержек и столкновений\n"
		"- Приземляй и отправляй рейсы вовремя\n\n"
		"Нажми 'НАЗАД' чтобы вернуться в меню");
	_rulesText.setCharacterSize(40);
	_rulesText.setFillColor(sf::Color::White);
	_rulesText.setPosition(100, 100);

	// Кнопка "НАЗАД"
	_backText.setFont(_data->assets.GetFont("menu_Font"));
	_backText.setString("НАЗАД");
	_backText.setCharacterSize(50);
	_backText.setFillColor(sf::Color::White);
	_backText.setPosition(100, SCREEN_HEIGHT - 120);
	*/

	_data->assets.LoadTexture("rules_Background", BACKGROUND_PNG);
	_data->assets.LoadFont("menu_Font", FONT_FOR_MENU);

	_background.setTexture(_data->assets.GetTexture("rules_Background"));

	_rulesText.setFont(_data->assets.GetFont("menu_Font"));
	_rulesText.setString("ПРАВИЛА:\n- Управляй самолётами...\n- Избегай ЧП\n- Следи за временем");
	_rulesText.setCharacterSize(36);
	_rulesText.setFillColor(sf::Color::White);
	_rulesText.setPosition(100, 100);

	// Кнопка назад
	backButton = std::make_unique<Button>(
		sf::Vector2f(200, 60),
		sf::Vector2f(100, SCREEN_HEIGHT - 100),
		"НАЗАД",
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
	backButton->draw(_data->window);
	_data->window.display();
}
