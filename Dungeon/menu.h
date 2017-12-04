/**********************************************************
Creator : Loup Olivier Gaven-Forest & Marie-Noelle Dussault
Date : November 27th 2017
File : menu.h
Goal : Create a menu
**********************************************************/

#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class menu {

private:
	vector<sf::RectangleShape> _menu;
	sf::Text _title;
	sf::RenderWindow _menuWindow;
	
public:
	int init();

};