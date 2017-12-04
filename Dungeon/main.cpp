#include <SFML/Graphics.hpp>
#include <iostream>
#include "Dungeon.h"
#include "position.h"

using namespace std;

void printMap(Dungeon map);

void main()
{
	//We create the map
	Dungeon map;
	map.init(15, 15, 15, 100, 100);
	map.createRooms();

	//We create the window
	sf::Window window(sf::VideoMode(1000, 600), "Dungeon Generator");
	window.setVerticalSyncEnabled(true);

	//We rint the map in the "world"
	printMap(map);

	// Open the window and keep it open until we close it
	while (window.isOpen())
	{
		// Lookout for events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// If the event is close, we close the window
			if (event.type == sf::Event::Closed)
				window.close();

			// If a key is pressed
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					cout << "The Up key was pressed" << endl;
					break;
				case sf::Keyboard::Down:
					cout << "The Down key was pressed" << endl;
					break;
				case sf::Keyboard::Right:
					cout << "The Right key was pressed" << endl;
					break;
				case sf::Keyboard::Left:
					cout << "The Left key was pressed" << endl;
					break;
				}
			}

		}

	}
}


void printMap(Dungeon map) {
	sf::Texture empty;
	sf::Texture wall;
	sf::Texture floor;
	sf::Texture door;

	//Load the Empty Texture
	if (!empty.loadFromFile("TileSetTP3.png", sf::IntRect(0, 0, 25, 25)))
		cout << "Couldn't load the Empty sprite" << endl;

	//Load the Wall Texture
	if (!wall.loadFromFile("TileSetTP3.png", sf::IntRect(25, 0, 25, 25)))
		cout << "Couldn't load the Wall sprite" << endl;

	//Load the Floor Texture
	if (!floor.loadFromFile("TileSetTP3.png", sf::IntRect(0, 25, 25, 25)))
		cout << "Couldn't load the Floor sprite" << endl;

	//Load the Door Texture
	if (!door.loadFromFile("TileSetTP3.png", sf::IntRect(25, 25, 25, 25)))
		cout << "Couldn't load the Door sprite" << endl;
}