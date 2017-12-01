/**********************************************************
Creator : Loup Olivier Gaven-Forest & Marie-Noelle Dussault
Date : November 27th 2017
File : position.h
Goal : Object keeping a position and a direction
**********************************************************/

#pragma once
#include <assert.h>
#include <istream>
#include <iostream>
using namespace std;

class position
{
private:
	int _posX;
	int _posY;
	char _direction;

public:
	position();							//Constructor without parameter
	position(int posX, int posY);		//Constructor with parameters
	~position();						//Destructor

	//Gets
	int getPosX()const;					//Get the X parameter of position
	int getPosY()const;					//Get the Y parameter of position
	char getDirection()const;			//Get the Direction parameter of position

	//Sets
	void setPosX(int);					//Set the X parameter of position
	void setPosY(int);					//Set the Y parameter of position
	void setPositionXY(int x, int y);	//Set the X and Y parameter of position
	void setDirection(char);			//Set the Direction parameter of position

	void print(ostream& sortie)const;	//Show the parameters of position on the screen
	void turn();						//Change the Direction parameter of position

	friend bool compare(position imp, position exp); // Compare 2 position and check if they are the same

	//Operator == calling the compare method of position
	bool operator==(const position& d);
};

//Operator << calling the print method of position
ostream& operator<<(ostream& out, const position& d);
