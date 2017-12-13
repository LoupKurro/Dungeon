/**********************************************************
Creator : Loup Olivier Gaven-Forest & Marie-Noelle Dussault
Date : December 6th 2017
File : character.h
Goal : Object used to keep the position of the character
and control his movement
**********************************************************/
#pragma once
#include "position.h"
#include "Dungeon.h"

using namespace std;

class character: public position
{
	private:
	public:
		character();
		character(int x, int y, char pos = 'N');
		bool moveUp(const Dungeon& d);
		bool moveDown(const Dungeon& d);
		bool moveRight(const Dungeon& d);
		bool moveLeft(const Dungeon& d);
};