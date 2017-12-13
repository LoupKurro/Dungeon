#include <iostream>
#include "windowMap.h"

void main()
{
	//Creatinp the window of the map
	windowMap window;
	window.createMap(20, 15, 15, 75, 75);
	window.init();
	window.eventHandle();
}