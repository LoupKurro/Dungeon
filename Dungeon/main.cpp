#include <iostream>
#include <SFML/Graphics.hpp>
#include "Dungeon.h"
#include "position.h"
#include "character.h"
#include "windowMap.h"

void main()
{
	//Creating the map
	Dungeon test;

	test.init(18, 12, 12, 50, 50);
	test.createRooms();
	test.createHallway();

	//Creatinp the window of the map
	windowMap window;
	window.createMap(20, 15, 15, 75, 75);
	window.init();
	window.eventHandle();
}