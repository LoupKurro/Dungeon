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
//#include "list.hpp"
#include <list>
#include <cmath>
#include <stack>

using namespace std;

class Dungeon :public mapTab<char>
{
private:
	//Const Variables for the creations of the rooms
	const int _minNbRooms = 2;	//Lowest number of rooms in the map
	const int _minSizeXRooms = 6; //Lowest size in X for the Rooms
	const int _minSizeYRooms = 6; //Lowest size in Y for the Rooms

								  //Variables for the creations of the rooms
	int _maxNbRooms;	//Highest number of rooms in the map
	int _maxSizeXRooms;	//Highest size in X for the Rooms
	int _maxSizeYRooms;	//Highest size in Y for the Rooms

	queue<position> doors; //Keep the positions of the doors created

	struct node
	{
		position pos;	//node position
		int distance;	//distance to next door
		int cost;		//cost of move to this node 
		int score;	//distance + cost
		position parent;//parent position		

		node() = default;	//use default constructor
							//contructor with parameters
		node(position po, position pa, int d = 0, int c = 0, int score = 0) {
			pos = po;
			parent = pa;
			distance = d;
			cost = c;
		};
		void calc(const node &e, const node &c) { //calculate distance, cost and score
			int xDist = abs(pos.getPosX() - e.pos.getPosX());
			int yDist = abs(pos.getPosY() - e.pos.getPosY());

			distance = (xDist + yDist); // manhatthan

			cost = c.cost + 1;
			score = distance + cost;
		}
	};

	node _start;			//starting node of a path
	node _end;				//ending node of a path
	list<node> _openList;	//list of checked nodes
	list<node> _closeList;	//list of choosen nodes
	stack<node> _path;		//keep nodes of a path
	list<node> _finalPath;	//keep nodes of final path

	list<node>::iterator _itO = _openList.begin();
	list<node>::iterator _itC = _closeList.begin();


public:
	void init(int rooms, int xRooms, int yRooms, int xMap, int yMap); //Set the 5 parameters of the map and fill the map with empty cases ('E')
	void clearDungeon();	//Put the parameters of the map back to 0
	void createRooms();		//Create the rooms in the map 
	void buildRoom(int xRoom, int yRoom, position startRoom);	//Build one rooom with the parameters 
	bool canCreate(int xRoom, int yRoom, position startRoom);	//Verify if the room can be created


	void createHallway();	//find and create a path to each doors in map
	void findPath();		//find a path between 2 doors
	bool checkAround(int i, node & c, node &n);	//check if neighbour is a valide node
	bool inClose(const node & n);	//check if node is in closeList
	bool inOpen(const node & n);	//check if node is in openList

	node findParent(const node &c);	//find parent of a node

	void addInScoreOrder(const node & n, list<node>& l);//add node in list ordered by score
	void addToFinalPath();			//add a path to the final path
	void addToMap();				//add final path to map
	node closest(list<node> &l);	//find closest path to a node

	int getLastDoorX()const;			//Return the last door X
	int getLastDoorY()const;			//Return the last door Y
};
