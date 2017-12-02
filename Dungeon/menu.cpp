#include "menu.h"

int menu::init()
{
	_menuWindow.create(sf::VideoMode(300, 200), "Dungeon");

	//titleText
	sf::Font font;
	font.loadFromFile("Candaraz.ttf");
	_title.setFont(font);
	_title.setString("Dungeon");
	_title.setCharacterSize(50);
	_title.setPosition(20, 20);
	_title.setFillColor(sf::Color::Yellow);

	sf::RectangleShape newGame;
	sf::RectangleShape loadGame;
	sf::RectangleShape exit;

	newGame.setSize(sf::Vector2f(280, 20));
	


	while (_menuWindow.isOpen()) {					// Is the window still opened?
		sf::Event event;							// We create an event
		
		while (_menuWindow.pollEvent(event)) {      // We fill the event from the window

			if (event.type == sf::Event::Closed)	// If the event is close window
				_menuWindow.close();				// We close it ;)
		}
		_menuWindow.clear(sf::Color::Black);
		_menuWindow.draw(_title);
		_menuWindow.display();
	}
	return 0;
}
