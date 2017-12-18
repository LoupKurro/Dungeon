#pragma once

#include "SFML\Graphics.hpp"
#include <iostream>
#include <string>

class gameMenu {
private:
	sf::RenderWindow _menuWindow;
	sf::Text _title;
	sf::Font font;

	sf::Text _name;
	
public:
	bool name();
	int mainMenu();
	sf::String loadMenu();
	
	void drawMenu(sf::RenderWindow &w, sf::Text t[], int size);
	void getName(sf::String &n);
};


