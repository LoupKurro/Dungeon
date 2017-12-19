/**********************************************************
Creator : Loup Olivier Gaven-Forest & Marie-Noelle Dussault
Date : December 13th 2017
File : windowMap.h
Goal : Object controlling the visual and the events of the map window
**********************************************************/

#include "windowMap.h"

//Constructor
windowMap::windowMap() {
	reset();
}

//Set back to the default parameters
void windowMap::reset()
{
	//Creating the window
	_window.create(sf::VideoMode(750, 750), "Dungeon Map");
	_window.setVerticalSyncEnabled(true);

	//Creating the hero texture and sprite
	if (!_tHero.loadFromFile("image.png"))
		std::cout << "The Hero Texture wasn't loaded correctly" << endl;
	_sHero.setTexture(_tHero);

	//Creating the View (Camera)
	_camera.setSize(sf::Vector2f(750, 750));
	_camera.setViewport(sf::FloatRect(0, 0, 1, 1));
}

//Create the map
void windowMap::createMap(int nbRoom, int xRoom, int yRoom, int xMap, int yMap)
{
	_map.init(nbRoom, xRoom, yRoom, xMap, yMap);
	_map.createRooms();
	_map.createHallway();

	//Set the sprite of the map
	setVisualMap();
	_sMap.setTexture(_rtMap);
	_sMap.setPosition(sf::Vector2f(0, 0));
}

//Initialise the hero and the visual of the created map
void windowMap::init() 
{
	//Creating character
	_hero.setPositionXY(_map.getLastDoorY(), _map.getLastDoorX());

	visualInit();
}

//Inititalise the visuals
void windowMap::visualInit()
{
	_sHero.setPosition(sf::Vector2f((_hero.getPosX() * 25), (_hero.getPosY() * 25)));

	//Setting the camera starting position
	_camera.setCenter((_hero.getPosX() * 25), (_hero.getPosY() * 25));

	//Link the view to the window
	_window.setView(_camera);

	//Show the map and Hero
	_window.draw(_sMap);
	_window.draw(_sHero);
	_window.display();
}

//Set the texture of the map 
void windowMap::setVisualMap()
{
	sf::RenderTexture tMap;
	if (!tMap.create(_map.nbLine() * 25, _map.nbCol() * 25))
		std::cout << "The Map Render Texture wasn't created correctly" << endl;


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

	tMap.clear();

	for (int i = 0; i < _map.nbLine(); i++) {
		for (int j = 0; j < _map.nbCol(); j++) {
			switch (_map.at(i, j)) {
			case 'E':
				sEmpty.setPosition(sf::Vector2f((j * 25), ((_map.nbLine() - i - 1) * 25)));
				tMap.draw(sEmpty);
				break;
			case 'W':
				sWall.setPosition(sf::Vector2f((j * 25), ((_map.nbLine() - i - 1) * 25)));
				tMap.draw(sWall);
				break;
			case 'F': case 'D':
				sFloor.setPosition(sf::Vector2f((j * 25), ((_map.nbLine() - i - 1) * 25)));
				tMap.draw(sFloor);
				break;
			case 'H':
				sHallway.setPosition(sf::Vector2f((j * 25), ((_map.nbLine() - i - 1) * 25)));
				tMap.draw(sHallway);
				break;

			}
		}
	}

	_rtMap =   tMap.getTexture();
}

//Handle the events link to the map
void windowMap::eventHandle(int id, mapInfo& information) {
	// Open the window and keep it open until we close it
	while (_window.isOpen())
	{
		// Lookout for events
		sf::Event event;
		while (_window.pollEvent(event))
		{
			// If the event is close, we close the window
			if (event.type == sf::Event::Closed)
			{
				information = save(id);
				_window.close();
			}


			// If a key is pressed
			if (event.type == sf::Event::KeyPressed)
			{
				_window.clear();
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					std::cout << "The Up key was pressed" << endl;
					_hero.moveUp(_map);
					break;
				case sf::Keyboard::Down:
					std::cout << "The Down key was pressed" << endl;
					_hero.moveDown(_map);
					break;
				case sf::Keyboard::Right:
					std::cout << "The Right key was pressed" << endl;
					_hero.moveRight(_map);
					break;
				case sf::Keyboard::Left:
					std::cout << "The Left key was pressed" << endl;
					_hero.moveLeft(_map);
					break;
				}
				_sHero.setPosition(sf::Vector2f((_hero.getPosX() * 25), (_hero.getPosY() * 25)));
				_camera.setCenter((_hero.getPosX() * 25), (_hero.getPosY() * 25));

				//Change the modification of the view and re-draw the map
				_window.setView(_camera);
				_window.draw(_sMap);
				_window.draw(_sHero);
				_window.display();
			}
		}
	}
}

//Save the map and return the informations of the map for the database
mapInfo windowMap::save(int id)
{
	string finDeFichier = ".txt";
	string nomFichier = "./Maps/" +to_string(id) + finDeFichier;
	ofstream fout;

	fout.open(nomFichier.c_str());
	_map.print(fout);
	fout.close();

	mapInfo information;
	information.linkMap = nomFichier;
	information.player = _hero;
	information.dimX = _map.nbLine();
	information.dimY = _map.nbCol();

	return information;
}

//Load the map as the informations of the map from the database
void windowMap::load(mapInfo& information)
{
	string nomFichier = information.linkMap;
	ifstream fin;

	_map.resize(information.dimX, information.dimY);
	fin.open(nomFichier.c_str());
	_map.read(fin);
	fin.close();

	_hero.setPosX(information.player.getPosX());
	_hero.setPosY(information.player.getPosY());

	visualInit();
}