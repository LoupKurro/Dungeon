#include <iostream>
#include "Dungeon.h"
#include "position.h"

using namespace std;

void main() {
	Dungeon test;
	test.init(20, 6, 7, 50, 50);
 	test.createRooms();
	test.print(cout);
	system("pause");
}