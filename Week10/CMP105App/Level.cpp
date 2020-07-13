#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	PlayerObject.texture.loadFromFile("gfx/MushroomTrans.png");
	PlayerObject.setTexture(&PlayerObject.texture);
	PlayerObject.setSize(sf::Vector2f(32, 32));
	PlayerObject.setCollisionBox(0, 0, 32, 32);
	PlayerObject.setPosition(500, 100);
	PlayerObject.setInput(input);


	// Tile Map building
	tileMap.loadTexture("gfx/marioTiles.png");

	GameObject tile;
	std::vector<GameObject> tiles;

	for (int i = 0; i < 7; i++) {
		tile.setSize(sf::Vector2f(32, 32));
		tile.setCollisionBox(0, 0, 32, 32);
		tile.setCollider(true);
		tiles.push_back(tile);
	}
	tiles[0].setCollider(false);
	tiles[0].setTextureRect(sf::IntRect(187, 51, 16, 16));
	tiles[1].setTextureRect(sf::IntRect(0, 0, 16, 16));
	tiles[2].setTextureRect(sf::IntRect(17, 0, 16, 16));
	tiles[3].setTextureRect(sf::IntRect(34, 0, 16, 16));
	tiles[4].setTextureRect(sf::IntRect(0, 34, 16, 16));
	tiles[5].setTextureRect(sf::IntRect(17, 34, 16, 16));
	tiles[6].setTextureRect(sf::IntRect(34, 34, 16, 16));

	tileMap.setTileSet(tiles);

	// Map dimensions
	sf::Vector2u mapSize(14, 6);// build map

	std::vector<int> map = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6,
		1, 2, 2, 3, 0, 0, 1, 2, 2, 3, 0, 0, 0, 0,
		4, 5, 5, 6, 0, 0, 4, 5, 5, 6, 0, 0, 0, 0,
	};

	tileMap.setTileMap(map, mapSize);
	tileMap.setPosition(sf::Vector2f(0, 408));
	tileMap.buildLevel();
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	PlayerObject.handleInput(dt);
}

// Update game objects
void Level::update(float dt)
{
	PlayerObject.update(dt);

	//Collision Check
	std::vector<GameObject>* world = tileMap.getLevel();
	for (int i = 0; i < (int)world->size(); i++) {
		// if collision check should occur
		if ((*world)[i].isCollider()) {
			if (Collision::checkBoundingBox(&PlayerObject, &(*world)[i])) {
				std::cout << "COLLISION RESPONSE: ";
				PlayerObject.collisionResponse(&(*world)[i]);
			}
		}
	}
}

// Render level
void Level::render()
{
	beginDraw();
	tileMap.render(window);
	window->draw(PlayerObject);
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}