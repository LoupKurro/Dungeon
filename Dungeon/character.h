/**********************************************************
Creator : Loup Olivier Gaven-Forest & Marie-Noelle Dussault
Date : December 6th 2017
File : character.h
Goal : Object 
**********************************************************/
#pragma once
#include "position.h"

using namespace std;

class character: public position
{
	private:
	public:
		bool moveUp();
		bool moveDown();
		bool moveRight();
		bool moveLeft();

		position getPosition();
		void setPosition(position pos);
};