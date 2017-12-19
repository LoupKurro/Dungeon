#include "stdafx.h"

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
		cout << name << endl;
		

		//recherche des infos sur le joueur
			
		int nbMap = sql.nbMap(name);
		cout << nbMap << endl;

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

