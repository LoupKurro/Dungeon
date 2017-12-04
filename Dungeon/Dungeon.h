/**********************************************************
Creator : Loup Olivier Gaven-Forest & Marie-Noelle Dussault
Date : November 29th 2017
File : Dungeon.h
Goal : Object creating the base of a dungeon (Rooms and Doors)
**********************************************************/
#pragma once

#include "mapTab.h"
#include "position.h"
#include <random>
#include <time.h> 
#include <queue>

using namespace std;

class Dungeon :public map<char>
{
private :
	//Const Variables for the creations of the rooms
	const int _minNbRooms = 2;	//Lowest number of rooms in the map
	const int _minSizeXRooms = 6; //Lowest size in X for the Rooms
	const int _minSizeYRooms = 6; //Lowest size in Y for the Rooms

	//Variables for the creations of the rooms
	int _maxNbRooms;	//Highest number of rooms in the map
	int _maxSizeXRooms;	//Highest size in X for the Rooms
	int _maxSizeYRooms;	//Highest size in Y for the Rooms

	 queue<position> doors; //Keep the positions of the doors created
public :
	void init(int rooms, int xRooms, int yRooms, int xMap, int yMap); //Set the 5 parameters of the map and fill the map with empty cases ('E')
	void clearDungeon(); //Put the parameters of the map back to 0
	void createRooms(); //Create the rooms in the map 
	void buildRoom(int xRoom, int yRoom, position startRoom);	//Build one rooom with the parameters 
	bool canCreate(int xRoom, int yRoom, position startRoom);	//Verify if the room can be created
};
