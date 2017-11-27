/**********************************************************
Creator : Loup Olivier Gaven-Forest & Marie-Noelle Dussault
Date : November 11th 2017
File : position.cpp
Goal : Object keeping a position and a direction
**********************************************************/

#include "position.h"

//Constructor without parameter
position::position()
{
	_posX = 0;
	_posY = 0;
	_direction = 'N';
}

//Constructor with parameter
position::position(int x, int y)
{
	_posX = x;
	_posY = y;
	_direction = 'N';
}

//Destructor
position::~position()
{
	_posX = 0;
	_posY = 0;
	_direction = ' ';
}

//Get the X parameter of position
int position::getPosX()const
{
	return _posX;
}

//Get the Y parameter of position
int position::getPosY()const
{
	return _posY;
}

//Get the Direction parameter of position
char position::getDirection()const
{
	return _direction;
}

//Set the X parameter of position
void position::setPosX(int x)
{
	assert(x >= 0);
	_posX = x;
}

//Set the Y parameter of position
void position::setPosY(int y)
{
	assert(y >= 0);
	_posY = y;
}

//Set the X and Y parameter of position
void position::setPositionXY(int x, int y)
{
	assert(x >= 0 && y >= 0);
	setPosX(x);
	setPosY(y);
}

//Set the Direction parameter of position
void position::setDirection(char direction)
{
	assert(direction == 'N' || direction == 'E' || direction == 'S' || direction == 'O' || direction == 'A');
	_direction = direction;
}

//Show the parameters of position on the screen
void position::print(ostream& sortie)const
{
	sortie << _posX << ' ' << _posY << ' ' << _direction;
}

//Change the Direction parameter of position
void position::turn()
{
	switch (_direction)
	{
	case 'N':
		_direction = 'E';
		break;

	case 'E':
		_direction = 'S';
		break;

	case 'S':
		_direction = 'O';
		break;

	case 'O':
		_direction = 'A';
		break;
	}
}

// Compare 2 position and check if they are the same 
bool compare(position imp, position exp)
{
	//Si les deux paramètres sont à la fin
	if (imp.getPosX() == exp.getPosX() && imp.getPosY() == exp.getPosY())
	{
		return true;
	}
	return false;
}

//Operator == calling the compare method of position
bool position::operator==(const position& d)
{
	return compare(*this, d);
}

//Operator << calling the print method of position
ostream& operator<<(ostream& sortie, const position& d)
{
	d.print(sortie);
	return sortie;
}