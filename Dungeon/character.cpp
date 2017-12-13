/**********************************************************
Creator : Loup Olivier Gaven-Forest & Marie-Noelle Dussault
Date : December 6th 2017
File : character.cpp
Goal : Object used to keep the position of the character 
and control his movement
**********************************************************/

#include "character.h"

using namespace std;

character::character() : position() {}
character::character(int x, int y, char pos) : position(x, y, pos) {}

bool character::moveUp(const Dungeon& d) {
	char caseNext = d.at(_posY - 1, _posX);
	if (_posY - 1 >= 0 && caseNext != 'W' && caseNext != 'E') {
		_posY = _posY - 1;
		return true;
	}
	return false;
}

bool character::moveDown(const Dungeon& d) {
	char caseNext = d.at(_posY + 1, _posX);
	if (_posY + 1 <= (d.nbCol()-1) && caseNext != 'W' && caseNext != 'E') {
		_posY = _posY + 1;
		return true;
	}
	return false;
}

bool character::moveRight(const Dungeon& d) {
	char caseNext = d.at(_posY, _posX + 1);
	if (_posX + 1 <= (d.nbLine()-1) && caseNext != 'W' && caseNext != 'E') {
		_posX = _posX + 1;
		return true;
	}
	return false;
}

bool character::moveLeft(const Dungeon& d) {
	char caseNext = d.at(_posY, _posX - 1);
	if (_posX - 1 >= 0 && caseNext != 'W' && caseNext != 'E') {
		_posX = _posX - 1;
		return true;
	}
	return false;
}