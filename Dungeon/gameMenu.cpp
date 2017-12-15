#include "gameMenu.h"
#include <iostream>

using namespace std;

int gameMenu::init()
{
	_menuWindow.create(sf::VideoMode(500, 500), "Dungeon");

	string str = "";
	_name.setString(str);
	_name.setPosition(180, 120);
	_name.setFont(font);
	_name.setFillColor(sf::Color::Yellow);
	_name.setCharacterSize(40);
	

	font.loadFromFile("DUNGRG.TTF");

	_title.setFont(font);
	_title.setString("Dungeon");
	_title.setCharacterSize(70);
	_title.setPosition(160, 20);
	_title.setFillColor(sf::Color::Yellow);

	button[0].setFont(font);
	button[0].setFillColor(sf::Color::Red);
	button[0].setString("New game");
	button[0].setCharacterSize(40);
	button[0].setPosition(180, 220);

	button[1].setFont(font);
	button[1].setFillColor(sf::Color::Red);
	button[1].setString("Load game");
	button[1].setCharacterSize(40);
	button[1].setPosition(180, 320);

	button[2].setFont(font);
	button[2].setFillColor(sf::Color::Red);
	button[2].setString("Exit");
	button[2].setCharacterSize(40);
	button[2].setPosition(220, 420);

	

	while (_menuWindow.isOpen()) {					// Is the window still opened?
		sf::Event event;							// We create an event

		while (_menuWindow.pollEvent(event)) {      // We fill the event from the window

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f position(sf::Mouse::getPosition(_menuWindow));

					for (int i = 0;i < 3;i++) {
						sf::FloatRect buttonPos = button[i].getGlobalBounds();

						if (buttonPos.contains(position))
							cout << "You have choose:  " << i << endl;
					}
				}
			}
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 128)
				{
					str += static_cast<char>(event.text.unicode);
					_name.setString(str);
					
				}
				_menuWindow.draw(_name);
				_menuWindow.display();

			}
			if (event.type == sf::Event::Closed)	// If the event is close window
				_menuWindow.close();				// We close it ;)
		}

		_menuWindow.clear(sf::Color::Black);
		drawMenu(_menuWindow);
		_menuWindow.draw(_name);
		_menuWindow.display();
	}
	return 0;
}

void gameMenu::drawMenu(sf::RenderWindow & window)
{
	window.draw(_title);

	for (int i = 0;i < 3;i++)
		window.draw(button[i]);

	window.draw(_name);
}


