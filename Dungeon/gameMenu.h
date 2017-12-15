#pragma once

#include "SFML\Graphics.hpp"
#include <iostream>

class gameMenu {
private:
	sf::RenderWindow _menuWindow;
	sf::Text _title;
	sf::Text button[3];
	sf::Font font;

	sf::Text _name;
	
public:
	int init();
	void drawMenu(sf::RenderWindow &window);


};


