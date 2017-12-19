#pragma once

#include "SFML\Graphics.hpp"
/**********************************************************
Creator : Loup Olivier Gaven-Forest & Marie-Noelle Dussault
Date : December 18th 2017
File : gameMenu.h
Goal : Manage and display menus
**********************************************************/

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
	int mainMenu(int nbMap);
	sf::String loadMenu();
	
	void drawMenu(sf::RenderWindow &w, sf::Text t[], int size);
	void getName(sf::String &n);
};


