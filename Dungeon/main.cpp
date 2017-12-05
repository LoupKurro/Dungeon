#include <iostream>
#include "Dungeon.h"
#include "position.h"

using namespace std;

void main() {
	Dungeon test;
	test.init(20, 6, 7, 50, 50);
	//test.init(3, 4, 4, 12, 12);
 	test.createRooms();
	test.print(cout);

	test.createHallway();
	test.print(cout);

	system("pause");
}