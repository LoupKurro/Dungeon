#include <iostream>
#include <SFML/Graphics.hpp>
#include "Dungeon.h"
#include "position.h"

void printMap(Dungeon& map, sf::RenderWindow& window);

void main()
{
	//Creating the map
	Dungeon test;

	test.init(18, 12, 12, 50, 50);
	test.createRooms();

	//Creating the window
	sf::RenderWindow window(sf::VideoMode(750, 750), "Dungeon Generator");
	window.setVerticalSyncEnabled(true);

	test.createHallway();


	//Creating the View (Camera)
	sf::View camera(sf::Vector2f(350, 350), sf::Vector2f(1500, 1500));
	camera.setViewport(sf::FloatRect(0, 0, 1, 1));
	camera.setCenter(750, 750);

	//Link the view to the window
	window.setView(camera);

	//Printing the map
	printMap(test, window);
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
					std::cout << "The Up key was pressed" << endl;
					camera.move(10, -25);
					window.setView(camera);
					break;
				case sf::Keyboard::Down:
					std::cout << "The Down key was pressed" << endl;
					camera.move(10, 25);
					window.setView(camera);					
					break;
				case sf::Keyboard::Right:
					std::cout << "The Right key was pressed" << endl;
					camera.move(25, 10);
					window.setView(camera);					
					break;
				case sf::Keyboard::Left:
					std::cout << "The Left key was pressed" << endl;
					camera.move(-25, 10);
					window.setView(camera);					
					break;
				}
			}

		}

	}
}

void printMap(Dungeon& map, sf::RenderWindow& window) {
	sf::Texture tEmpty;
	sf::Texture tWall;
	sf::Texture tFloor;
	sf::Texture tHallway;

	sf::Sprite sEmpty;
	sf::Sprite sWall;
	sf::Sprite sFloor;
	sf::Sprite sHallway;

	

	if (!tEmpty.loadFromFile("TileSetTP3.png", sf::IntRect(0, 0, 25, 25)))
		std::cout << "The Empty Texture wasn't loaded correctly" << endl;
	else
		sEmpty.setTexture(tEmpty);

	if (!tWall.loadFromFile("TileSetTP3.png", sf::IntRect(25, 0, 25, 25)))
		std::cout << "The Wall Texture wasn't loaded correctly" << endl;
	else 
		sWall.setTexture(tWall);


	if (!tFloor.loadFromFile("TileSetTP3.png", sf::IntRect(25, 25, 25, 25)))
		std::cout << "The Floor Texture wasn't loaded correctly" << endl;
	else {
		sFloor.setTexture(tFloor);
		sFloor.setColor(sf::Color(165, 150, 150));
	}

	if (!tHallway.loadFromFile("TileSetTP3.png", sf::IntRect(0, 25, 25, 25)))
		std::cout << "The Hallway Texture wasn't loaded correctly" << endl;
	else
		sHallway.setTexture(tHallway);

	for (int i = 0; i < map.nbLine(); i++) {
		for (int j = 0; j < map.nbCol(); j++) {
			switch (map.at(i, j)) {
			case 'E':
				sEmpty.setPosition(sf::Vector2f((i*25), (j * 25)));
				window.draw(sEmpty);
				break;
			case 'W':
				sWall.setPosition(sf::Vector2f((i * 25), (j * 25)));
				window.draw(sWall);
				break;
			case 'F': case 'D' :
				sFloor.setPosition(sf::Vector2f((i * 25), (j * 25)));
				window.draw(sFloor);
				break;
			case 'H':
				sHallway.setPosition(sf::Vector2f((i * 25), (j * 25)));
				window.draw(sHallway);
				break;

			}
		}
	}
	window.display();
}