/**********************************************************
Creator : Loup Olivier Gaven-Forest & Marie-Noelle Dussault
Date : December 13th 2017
File : windowMap.h
Goal : Object controlling the visual and the events of the map window
**********************************************************/

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Dungeon.h"
#include "position.h"
#include "character.h"
#include "mapInfo.h"

class windowMap
{
private:
	//Window
	sf::RenderWindow _window;

	//Hero
	character _hero;
	sf::Texture _tHero;
	sf::Sprite _sHero;

	//Camera
	sf::View _camera;

	//Map
	Dungeon _map;
	sf::Texture _rtMap;
	sf::Sprite _sMap;

	//Private Functions
	void setVisualMap();		//Set the texture of the map 
public:
	windowMap();	//Constructor
	void reset();	//Set back to the default parameters
	void createMap(int nbRoom, int xRoom, int yRoom, int xMap, int yMap);	//Create the map
	void init();	//Initialise the visual with the created map
	void eventHandle(int id, mapInfo& information);  //Handle the events link to the map
	mapInfo save(int id);		//Save the map and return the informations of the map for the database
};