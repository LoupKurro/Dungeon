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
	assert(xRooms >= (_minSizeXRooms - 2) && yRooms >= (_minSizeYRooms - 2));
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
			if (i == startRoom.getPosX() || i == startRoom.getPosX() + xRoom - 1 || j == startRoom.getPosY() || j == startRoom.getPosY() + yRoom - 1) {
				at(i, j) = 'W';

				//If we aren't at a corner (a case were we can't put a door)
				if (!((i == startRoom.getPosX() && j == startRoom.getPosY()) || (i == startRoom.getPosX() + xRoom - 1 && j == startRoom.getPosY()) || (i == startRoom.getPosX() && j == startRoom.getPosY() + yRoom - 1) || (i == startRoom.getPosX() + xRoom - 1 && j == startRoom.getPosY() + yRoom - 1)))
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

//find and create a path to each doors in map
void Dungeon::createHallway()
{
	_end = node(doors.front(), doors.front());
	doors.pop();

	while (!doors.empty()) {
		_openList.clear();
		_closeList.clear();
		if (_finalPath.empty()) {	//first iteration
			_start = _end;			//take 2 first doors
			_end = node(doors.front(), doors.front());
		}
		else {
			_end = node(doors.front(), doors.front());
			_start = closest(_finalPath);	//find the closest path to next door
		}
		doors.pop();
		_start.calc(_end, _start);	//calculate distance, cost and score 
		findPath();					// find a path 
		addToFinalPath();			//add it to final path
	}
	addToMap();						//add final path to map
}

//find a path between 2 doors
void Dungeon::findPath() {
	node current;
	node newNode;

	_itO = _openList.begin();
	_itC = _closeList.begin();
	_openList.insert(_itO, _start);	//place the first doors in openList

	do {
		_itO = _openList.begin();

		current = *_itO;			//current have the lower score in openList 
		_closeList.insert(_itC, current);	//place current in closedList
		_openList.erase(_itO);				//remove current of closedList	

		if (current.pos == _end.pos) {		//if current node is final destination
			while (current.pos != _start.pos) {
				current = findParent(current);
				_path.push(current);		//build the path
			}
			return;
		}
		for (int i = 0; i < 4; i++) {		//for each of 4 neighbours positions

			if (checkAround(i, current, newNode))	//check if position is a valid node
				if (!inClose(newNode))				//if the new node is not on closelist
					if (!inOpen(newNode))			//or openList
						addInScoreOrder(newNode, _openList);	//add it to openlist ordored by score
					else if (newNode.score < (*_itO).score)//if new node is in openlist having a lowest sore
						(*_itO) = newNode;			//the new node replaces the old one
		}
	} while (!_openList.empty());

}

//check if neighbour is a valid node
bool Dungeon::checkAround(int i, node & c, node & n)
{
	position newPos = c.pos;

	switch (i)
	{
	case 0:		//up
		if (newPos.getPosX() - 1 >= 0 && newPos.getPosX() - 1 <_nbLine)
			newPos.setPosX(newPos.getPosX() - 1);
		break;
	case 1:		//down
		if (newPos.getPosX() + 1 >= 0 && newPos.getPosX() + 1 <_nbLine)
			newPos.setPosX(newPos.getPosX() + 1);
		break;
	case 2:		//left
		if (newPos.getPosY() - 1 >= 0 && newPos.getPosY() - 1 <_nbLine)
			newPos.setPosY(newPos.getPosY() - 1);
		break;
	case 3:		//right
		if (newPos.getPosY() + 1 >= 0 && newPos.getPosY() + 1 <_nbLine)
			newPos.setPosY(newPos.getPosY() + 1);
	default:
		break;
	}

	int x = newPos.getPosX();
	int y = newPos.getPosY();

	if (at(x, y) == 'E' || at(x, y) == 'H' || at(x, y) == 'D') {
		n = node(newPos, c.pos);	//create a node a this position
		n.calc(_end, c);			//calculate distance, cost and score
		return true;
	}
	return false;
}

//check if node is in closeList
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
//check if node is in openList
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
//find parent of a node
Dungeon::node Dungeon::findParent(const node & c)
{
	_itC = _closeList.begin();

	while (_itC != _closeList.end()) {
		if ((*_itC).pos == c.parent)
			return *_itC;
		_itC++;
	}
}
//add node in list ordered by score
void Dungeon::addInScoreOrder(const node & n, list<node> &l)
{
	list<node>::iterator it;
	it = l.begin();

	while (it != l.end()) {
		if (n.score < (*it).score) {
			l.insert(it, n);
			return;
		}
		it++;
	}
	l.insert(it, n);
}

//add a path to the final path
void Dungeon::addToFinalPath()
{
	list<node>::iterator it = _finalPath.begin();

	while (!_path.empty())
	{
		_finalPath.insert(it, _path.top());
		_path.pop();
	}
}

//add final path to map
void Dungeon::addToMap()
{
	list<node>::iterator it = _finalPath.begin();

	while (it != _finalPath.end()) {
		if (at((*it).pos.getPosX(), (*it).pos.getPosY()) != 'D')
			at((*it).pos.getPosX(), (*it).pos.getPosY()) = 'H';
		it++;
	}
}

//find closest path to a node
Dungeon::node Dungeon::closest(list<node> &l)
{
	list<node>::iterator it = l.begin();

	node closest = *it;
	closest.calc(_end, closest);

	while (it != l.end()) {

		(*it).calc(_end, (*it));

		if ((*it).distance < closest.distance) {
			closest = *it;
		}
		it++;
	}
	return closest;
}