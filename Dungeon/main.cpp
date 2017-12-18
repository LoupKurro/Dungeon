#include <iostream>
#include <SFML/Graphics.hpp>
#include "Dungeon.h"
#include "position.h"
#include "gameMenu.h"
#include "windowMap.h"

void main()
{
	gameMenu menu;
	
	if (menu.name()) {
		sf::String playerName;
		menu.getName(playerName);
		string name = playerName;
		cout << name;
		//recherche des infos sur le joueur

		sf::String gameToLoad = "";
		int choice = 1;		
		
		while (choice == 1 && gameToLoad == "") {
			choice = menu.mainMenu();
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



