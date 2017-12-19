#include <iostream>
#include <SFML/Graphics.hpp>
#include "Dungeon.h"
#include "position.h"
#include "gameMenu.h"
#include "windowMap.h"
#include "sqlConnect.h"

void main()
{
	gameMenu menu;
	sqlConnect sql;

	sql.connexion();
	
	if (menu.name()) {
		sf::String playerName;
		menu.getName(playerName);
		string pName = playerName;
		char *name =(char*)pName.c_str();
		cout << name;


		//recherche des infos sur le joueur
			
		int nbGameToLoad;
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



