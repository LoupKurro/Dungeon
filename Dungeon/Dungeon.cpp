/**********************************************************
Creator : Loup Olivier Gaven-Forest & Marie-Noelle Dussault
Date : November 29th 2017
File : Dungeon.cpp
Goal : Object creating the base of a dungeon (Rooms and Doors)
**********************************************************/

#include "Dungeon.h"

//Set the 5 parameters of the map and fill the map with empty cases ('E')
void Dungeon::init(int rooms, int xRooms, int yRooms, int xMap, int yMap) {
	assert(rooms >= _minNbRooms);
	assert(xRooms >= (_minSizeXRooms-2) && yRooms >= (_minSizeYRooms-2));
	assert(xMap >= 50 && yMap >= 50);	//Assure that the map will be 50x50 or more
	
	_maxNbRooms = rooms;
	_maxSizeXRooms = xRooms + 2;	//Add 2 for the Empty cases around the room
	_maxSizeYRooms = yRooms + 2;	//Add 2 for the Empty cases around the room
	resize(yMap, xMap);
	for (int i = 0; i < yMap; i++) {
		for (int j = 0; j < xMap; j++) {
			at(i, j) = 'E';
		}
	}

	while (!doors.empty()) {
		doors.pop();
	}

	srand(time(NULL));	//Init Random
}

//Put the parameters of the map back to 0
void Dungeon::clearDungeon() {
	_maxNbRooms = _maxSizeXRooms = _maxSizeYRooms = 0;
	resize(0, 0);
	while (!doors.empty()) {
		doors.pop();
	}
}

//Create the rooms in the map 
void Dungeon::createRooms() {
	int rooms = rand() % (_maxNbRooms - _minNbRooms) + _minNbRooms;
	for (int i = 0; i <= rooms; i++) {

		int xRoom, yRoom;
		position startRoom;

		do {
			xRoom = rand() % ((_maxSizeXRooms + 2) - _minSizeXRooms) + _minSizeXRooms;
			yRoom = rand() % ((_maxSizeYRooms + 2) - _minSizeYRooms) + _minSizeYRooms;
			startRoom.setPositionXY(rand() % (_nbLine - 1), rand() % (_nbCol - 1));

		//Check if the room can be created at that position with those dimensions and if not we try again
		} while (canCreate(xRoom, yRoom, startRoom) == false);

		//Change the position and dimmensions of the room to keep empty spaces between each rooms
		startRoom.setPositionXY(startRoom.getPosX() + 1, startRoom.getPosY() + 1);
		xRoom -= 2;
		yRoom -= 2;
		buildRoom(xRoom, yRoom, startRoom);
	}
}

//Build one rooom with the parameters 
void Dungeon::buildRoom(int xRoom, int yRoom, position startRoom) {
	int perimeter = (xRoom - 2) * 2 + (yRoom - 2) * 2;
	int doorPosition = rand() % perimeter;
	int doorWall = 0;		//Count the number of wall passed were we could have build a door

	for (int i = startRoom.getPosX(); i < startRoom.getPosX() + xRoom; i++) {
		for (int j = startRoom.getPosY(); j < startRoom.getPosY() + yRoom; j++) {
			//If we are at a Wall position
			if (i == startRoom.getPosX() || i == startRoom.getPosX() + xRoom - 1|| j == startRoom.getPosY() || j == startRoom.getPosY() + yRoom - 1) {
				at(i, j) = 'W';

				//If we aren't at a corner (a case were we can't put a door)
				if (!((i == startRoom.getPosX() && j == startRoom.getPosY()) || (i == startRoom.getPosX() + xRoom - 1 && j == startRoom.getPosY()) || (i == startRoom.getPosX() && j == startRoom.getPosY() + yRoom -1) || (i == startRoom.getPosX() + xRoom - 1 && j == startRoom.getPosY() + yRoom - 1)))
				{
					//If we are at the position of the door
					if (doorWall == doorPosition) {
						at(i, j) = 'D';
						position door(i, j);
						doors.push(door);
					}
					doorWall++;
				}
			}
			else
				at(i, j) = 'F';
		}
	}
}

//Verify if the room can be created
bool Dungeon::canCreate(int xRoom, int yRoom, position startRoom) {
	for (int i = startRoom.getPosX(); i < startRoom.getPosX() + xRoom; i++) {
		for (int j = startRoom.getPosY(); j < startRoom.getPosY() + yRoom; j++) {
			if (i < _nbLine && j < _nbCol) {
				if (at(i, j) != 'E')
					return false;
			}
			else
				return false;
		}
	}
	return true;
}

//Create the door in a room 
void Dungeon::createDoor() {

}