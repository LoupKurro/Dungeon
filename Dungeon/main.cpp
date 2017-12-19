#include "stdafx.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Dungeon.h"
#include "position.h"
#include "gameMenu.h"
#include "windowMap.h"
#include "sqlConnect.h"
#include "mapInfo.h"

void main()
{
	gameMenu menu;
	sqlConnect sql;
	
	if (menu.name()) {
		sf::String playerName;
		string pName = playerName;
		menu.getName(playerName);
		char *name =(char*)pName.c_str();
		cout << name << endl;
		
		int nbMap = sql.nbMap(name);
		cout << nbMap << endl;
		int nextId = sql.nextMapId() + 1;
		cout<< "Next map id  " << nextId << endl;

		sf::String plMap[10];
		sf::String gameToLoad = "";
		int choice = 1;		
		
		while (choice == 1 && gameToLoad == "") {
			choice = menu.mainMenu(nbMap);
			if (choice == 1)
				gameToLoad = menu.loadMenu();
		}

		if (choice == 0)
		{
			windowMap window;
			window.createMap(20, 15, 15, 75, 75);
			window.init();
			window.eventHandle();
			

		}
	}	
}

