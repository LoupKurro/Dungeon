


#include <SFML/Graphics.hpp>
#include "menu.h"
#include <iostream>
#include "Dungeon.h"
#include "position.h"

using namespace std;

int main(int argc, const char **argv) {

	menu m;
	
	m.init();
	return 0;
  
	Dungeon test;
	test.init(20, 6, 7, 50, 50);
 	test.createRooms();
	test.print(cout);

	//test.createHallway();
	//test.print(cout);

	system("pause");
}