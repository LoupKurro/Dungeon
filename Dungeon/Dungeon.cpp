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
	//assert(xMap >= 50 && yMap >= 50);	//Assure that the map will be 50x50 or more
	
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
						position door(i, j, 'N');
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


void Dungeon::createHallway()
{
	_end = node(doors.front(), doors.front());
	doors.pop();

	while (!doors.empty()){
		_openList.clear();
		_closeList.clear();
		_start = _end;
		_end = node(doors.front(), doors.front());
		doors.pop();
		_start.calc(_end, _start);
		findPath();
	
		while (!_path.empty()) {
			node toAdd = _path.top();
			_path.pop();
			if(at(toAdd.pos.getPosX(), toAdd.pos.getPosY()) != 'D')
				at(toAdd.pos.getPosX(), toAdd.pos.getPosY()) = 'H';
		}
	}
}

void Dungeon::findPath() {
	node current;
	node newNode;

	_itO = _openList.begin();
	_itC = _closeList.begin();
	_openList.insert(_itO, _start);

	do {
		_itO = _openList.begin();
		
		current = *_itO;
		_closeList.insert(_itC, current);
		_openList.erase(_itO);

		if (current.pos == _end.pos) {
			while (current.pos != _start.pos) {

				current = findParent(current);
				_path.push(current);

			}
			return;
		}

		for (int i = 0; i < 4; i++) {

			if (checkAround(i, current, newNode))
				if (!inClose(newNode))
					if (!inOpen(newNode))
						addToOpen(newNode);
					else if (newNode.score < (*_itO).score)
						(*_itO) = newNode;
		}
	} while (!_openList.empty());

}


bool Dungeon::checkAround(int i, node & c, node & n)
{
	position newPos = c.pos;

	switch (i)
	{
	case 0:
		if(newPos.getPosX() - 1 >= 0 && newPos.getPosX() - 1 <_nbLine)
			newPos.setPosX(newPos.getPosX() - 1);
		break;
	case 1:
		if (newPos.getPosX() + 1 >= 0 && newPos.getPosX() + 1 <_nbLine)
			newPos.setPosX(newPos.getPosX() + 1);
		break;
	case 2:
		if (newPos.getPosY() - 1 >= 0 && newPos.getPosY() - 1 <_nbLine)
			newPos.setPosY(newPos.getPosY() - 1);
		break;
	case 3:
		if (newPos.getPosY() + 1 >= 0 && newPos.getPosY() + 1 <_nbLine)
			newPos.setPosY(newPos.getPosY() + 1);
	default:
		break;
	}

	int x = newPos.getPosX();
	int y = newPos.getPosY();

	
	if (at(x, y) == 'E' || at(x, y) == 'H' || at(x, y) == 'D') {
		n = node(newPos, c.pos);
		n.calc(_end, c);
		return true;
	}
	return false;
}

bool Dungeon::inClose(const node & n)
{
	_itC = _closeList.begin();

	while (_itC != _closeList.end()) {
		if ((*_itC).pos == n.pos)
			return true;

		_itC++;
	}
	return false;
}

bool Dungeon::inOpen(const node & n)
{
	_itO = _openList.begin();

	while (_itO != _openList.end()) {
		if ((*_itO).pos == n.pos)
			return true;
		_itO++;
	}
	return false;

}

void Dungeon::addToOpen(const node & n)
{
	_itO = _openList.begin();

	while (_itO != _openList.end()) {	
		if (n.score < (*_itO).score) {
			_openList.insert(_itO, n);
			return;
		}			
		_itO++;
	}
	_openList.insert(_itO, n);
}

Dungeon::node Dungeon::findParent(const node & c)
{
	_itC = _closeList.begin();

	while (_itC != _closeList.end()) {
		if ((*_itC).pos == c.parent)
			return *_itC;
		_itC++;
	}
}







