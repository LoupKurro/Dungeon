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
#include "list.hpp"
//#include <list>
#include <cmath>

using namespace std;

class Dungeon :public map<char>
{
private :
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
		position pos;
		int distance;
		int cost;
		int score;
		position parent;		

		node() = default;
		node(position po, position pa,  int d = 0, int c = 0, int score = 0 ) {
			pos = po;
			parent = pa;
			distance = d;
			cost = c;
		};
		void calc(const node &e, const node &c) {
			int xDist = abs(pos.getPosX() - e.pos.getPosX());
			int yDist = abs(pos.getPosY() - e.pos.getPosY());

			distance = (xDist + yDist)*5;
			cost = c.cost + 1;
			score = distance + cost;
		}
	 };

	node _start, _end;
	list<node> _openList;
	list<node> _closeList;
	list<node> _path;

	list<node>::iterator _itO = _openList.begin();
	list<node>::iterator _itC = _closeList.begin();
	list<node>::iterator _itP = _path.begin();

public :
	void init(int rooms, int xRooms, int yRooms, int xMap, int yMap); //Set the 5 parameters of the map and fill the map with empty cases ('E')
	void clearDungeon(); //Put the parameters of the map back to 0
	void createRooms(); //Create the rooms in the map 
	void buildRoom(int xRoom, int yRoom, position startRoom);	//Build one rooom with the parameters 
	bool canCreate(int xRoom, int yRoom, position startRoom);	//Verify if the room can be created
	

	void createHallway();
	void findPath();
	bool checkAround(int i, node & c, node &n);
	void ifIsInTheLists(const node & n);

	//bool isInList(list<node> &l, node & n);
	
	


	/*void pathfinding(node start, node end, list<node> &path);
	void checkAround(node &c, node &e, list<node> &w);
	void addNode(position &p, list<node>& w, node &e, node &s);
	node & findBestMove(list<node> &w, node &c);*/
};
