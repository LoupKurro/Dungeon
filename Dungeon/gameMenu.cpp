#include "gameMenu.h"
#include <iostream>

using namespace std;


bool gameMenu::name()
{
	_menuWindow.create(sf::VideoMode(600, 300), "Dungeon - Enter your name");
	font.loadFromFile("DUNGRG.TTF");

	_title.setFont(font);
	_title.setString("Welcome to Dungeon");
	_title.setCharacterSize(70);
	_title.setPosition(80, 20);
	_title.setFillColor(sf::Color::Yellow);

	sf::Text please;
	please.setFont(font);
	please.setString("Please enter your name: ");
	please.setCharacterSize(30);
	please.setPosition(80, 100);
	please.setFillColor(sf::Color::Yellow);

	string str = "";
	_name.setString(str);
	_name.setPosition(80, 160);
	_name.setFont(font);
	_name.setFillColor(sf::Color::Red);
	_name.setCharacterSize(70);

	while (_menuWindow.isOpen()) {					// Is the window still opened?
		sf::Event event;							// We create an event

		while (_menuWindow.pollEvent(event)) {      // We fill the event from the window

			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Return)
					if (str.size() > 0) {
						_menuWindow.close();
						return true;
					}
			if (event.type == sf::Event::TextEntered) {

				switch (event.text.unicode)
				{
				case '\b':
					if (str.size() > 0)
						str.erase(str.size() - 1, 1);
					break;
				case '\n':
					break;
				default:
					if (event.text.unicode > 65 && event.text.unicode < 122) {
						str += static_cast<char>(event.text.unicode);
						_name.setString(str);
					}
					break;
				}

				_menuWindow.draw(_name);
				_menuWindow.display();

			}
			if (event.type == sf::Event::Closed) {	// If the event is close window
				_menuWindow.close();				// We close it ;)
				return false;
			}
		}

		_menuWindow.clear(sf::Color::Black);
		_menuWindow.draw(_title);
		_menuWindow.draw(please);
		_menuWindow.draw(_name);
		_menuWindow.display();
	}
}


int gameMenu::mainMenu(int nbMap)
{
	_menuWindow.create(sf::VideoMode(500, 500), "Dungeon - Menu");
	font.loadFromFile("DUNGRG.TTF");
	sf::Text button[3];

	_title.setFont(font);
	_title.setString("Dungeon");
	_title.setCharacterSize(70);
	_title.setPosition(160, 20);
	_title.setFillColor(sf::Color::Yellow);

	button[0].setFont(font);
	button[0].setFillColor(sf::Color::White);
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

	int choice = 0;

	if (nbMap == 0)
		button[1].setFillColor(sf::Color::Black);

	while (_menuWindow.isOpen()) {					// Is the window still opened?
		sf::Event event;							// We create an event

		while (_menuWindow.pollEvent(event)) {      // We fill the event from the window

			switch (event.type)
			{
			case (sf::Event::Closed):
				_menuWindow.close();				// We close it ;)
				return 2;
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if (choice > 0) {
						button[choice].setFillColor(sf::Color::Red);
						choice -= 1;
						if (button[choice].getFillColor() == sf::Color::Black)
							choice -= 1;
						button[choice].setFillColor(sf::Color::White);
					}
					break;

				case sf::Keyboard::Down:
					if (choice < 2) {
						button[choice].setFillColor(sf::Color::Red);
						choice += 1;
						if (button[choice].getFillColor() == sf::Color::Black)
							choice += 1;
						button[choice].setFillColor(sf::Color::White);
					}
					break;

				case sf::Keyboard::Return:
					_menuWindow.close();
					return choice;
					break;

				default:
					break;
				}

			default:
				break;
			}
		}

		_menuWindow.clear(sf::Color::Black);
		drawMenu(_menuWindow, button, 3);
		_menuWindow.display();
	}
	return 2;
}

sf::String gameMenu::loadMenu()
{
	sf::RenderWindow loadWindow;
	loadWindow.create(sf::VideoMode(600, 500), "Dungeon - Load menu");
	font.loadFromFile("DUNGRG.TTF");

	_title.setFont(font);
	_title.setString("Dungeon - Load a game");
	_title.setCharacterSize(70);
	_title.setPosition(60, 20);
	_title.setFillColor(sf::Color::Yellow);

	//pour avoir quelque chose a afficher
	string plGames[10];
	for (int i = 0; i < 10; i++)
		plGames[i] = "Empty";

	sf::Text savedGame[10];

	for (int i = 0; i < 10;i++) {
		savedGame[i].setFont(font);
		savedGame[i].setString(plGames[i]);
		savedGame[i].setCharacterSize(25);
		savedGame[i].setPosition(120, 120 + 25*i);
		savedGame[i].setFillColor(sf::Color::Red);

	}
	int choice = 0;
	savedGame[choice].setFillColor(sf::Color::White);


	while (loadWindow.isOpen()) {					// Is the window still opened?
		sf::Event event;							// We create an event

		while (loadWindow.pollEvent(event)) {      // We fill the event from the window

			switch (event.type)
			{
			case (sf::Event::Closed):
				//mainMenu();
				loadWindow.close();				// We close it ;)
				return "";
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if (choice > 0) {
						savedGame[choice].setFillColor(sf::Color::Red);
						choice -= 1;
						savedGame[choice].setFillColor(sf::Color::White);
					}
					break;

				case sf::Keyboard::Down:
					if (choice < 9) {
						savedGame[choice].setFillColor(sf::Color::Red);
						choice += 1;
						savedGame[choice].setFillColor(sf::Color::White);
					}
					break;

				case sf::Keyboard::Return:
					loadWindow.close();
					return savedGame[choice].getString();
					break;
				default:
					break;

				}
				break;
			default:
				break;
			}
		}

		loadWindow.clear(sf::Color::Black);
		drawMenu(loadWindow, savedGame, 10);
		loadWindow.display();
	}
}



void gameMenu::drawMenu(sf::RenderWindow &w, sf::Text t[], int size)
{
	w.draw(_title);
	for (int i = 0;i <size;i++)
		w.draw(t[i]);
}

void gameMenu::getName(sf::String & n)
{
	n = _name.getString();
}







