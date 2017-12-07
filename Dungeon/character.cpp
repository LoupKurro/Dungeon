/**********************************************************
Creator : Loup Olivier Gaven-Forest & Marie-Noelle Dussault
Date : December 6th 2017
File : character.cpp
Goal : Object
**********************************************************/

#include "character.h"

using namespace std;

bool character::moveUp() {
	if (_posX - 1 >= 0) {
		_posX = _posX - 1;
		return true;
	}
	return false;
}

bool character::moveDown() {
	if (_posX + 1 >= 0) {
		_posX = _posX + 1;
		return true;
	}
	return false;
}

bool character::moveRight() {
	if (_posY + 1 >= 0) {
		_posY = _posY + 1;
		return true;
	}
	return false;
}

bool character::moveLeft() {
	if (_posY - 1 >= 0) {
		_posY = _posY - 1;
		return true;
	}
	return false;
}

position character::getPosition() {

}

void character::setPosition(position pos) {

}