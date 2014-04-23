/***********************************************************************
     * File       : map_base.cpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Map
     * constructor

***********************************************************************/
fired::Map::Map(fired::Camera *_cam, fired::World *_world) {
	cam      = _cam;
	world    = _world;

	visibleTiles.x = settings->window.width  / TILE_SIZE + 2;
	visibleTiles.y = settings->window.height / TILE_SIZE + 2;

	mapLoad(this, "data/maps/test.map");

	int lightCount = (visibleTiles.x + LIGHT_OFFSCREEN_TILES * 2) * (visibleTiles.x + LIGHT_OFFSCREEN_TILES * 2);
	for (int i = 0; i < LIGHT_MAX_LIGHTLEVEL; i++) lightTiles[i] = new fired::Tile*[lightCount];
}



/***********************************************************************
     * Map
     * destructor

***********************************************************************/
fired::Map::~Map() {
	for (int i = 0; i < LIGHT_MAX_LIGHTLEVEL; delete lightTiles[i++]);
	for (int i = 0; i < sizeX; delete tiles[i++]);
	delete tiles;
	delete weather;

	deleteList(objects);
	deleteList(lights);
}



/***********************************************************************
     * Map
     * update

***********************************************************************/
void fired::Map::update() {
	sf::Vector2f offset = cam->offset;
	resetLight();

	biome->bgSprite->setPosition(offset);
	biome->bgSprite->setTextureRect(sf::IntRect(offset.x / 3.0f, 0, settings->window.width * biome->bgScale, biome->bgTex->getSize().y));

	render();
}



/***********************************************************************
     * Map
     * render

***********************************************************************/
void fired::Map::render() {
	app->draw(*biome->bgSprite);
	if (weather) weather->update();

	sf::Vector2i from((int)(cam->offset.x / TILE_SIZE), (int)(cam->offset.y / TILE_SIZE));
	sf::Vector2i to(from + visibleTiles);

	if (from.x < 0  ) from.x = 0;
	if (from.y < 0  ) from.y = 0;
	if (to.x > sizeX) to.x = sizeX;
	if (to.y > sizeY) to.y = sizeY;

	for (int i = from.x; i < to.x; i++)
		for (int j = from.y; j < to.y; j++)
			tiles[i][j].render();

	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->render(this);

	updateList(lights);
}



/***********************************************************************
     * Map
     * spawn

***********************************************************************/
void fired::Map::spawn() {
	if (biome->creatures.size() == 0) return;

	int toSpawn = rand() % biome->creatures.size();
	world->spawn(sf::Vector2f(2200 + rand() % 200, 560), biome->creatures[toSpawn]);
}



/***********************************************************************
     * Map
     * setWeather

***********************************************************************/
void fired::Map::setWeather() {
	weather = biome->getWeather(world);
	if (weather) weather->fill();
}



/***********************************************************************
     * Map
     * findTile

***********************************************************************/
void fired::Map::findTile(int i, int j) {
	int resultTile;
	int top    = 0;
	int left   = 0;
	int right  = 0;
	int bottom = 0;

	if (i == 0) left = 1;
	else if (tiles[i-1][j].tileset && tiles[i][j].tileset && tiles[i-1][j].isWall >= tiles[i][j].isWall) left = 1;

	if (i == sizeX - 1) right = 1;
	else if (tiles[i+1][j].tileset && tiles[i][j].tileset && tiles[i+1][j].isWall >= tiles[i][j].isWall) right = 1;

	if (j == 0) top = 1;
	else if (tiles[i][j-1].tileset && tiles[i][j].tileset && tiles[i][j-1].isWall >= tiles[i][j].isWall) top = 1;

	if (j == sizeY - 1) bottom = 1;
	else if (tiles[i][j+1].tileset && tiles[i][j].tileset && tiles[i][j+1].isWall >= tiles[i][j].isWall) bottom = 1;

	resultTile = left   * 1 +
	             right  * 2 +
	             top    * 4 +
	             bottom * 8;

	tiles[i][j].setTile(resultTile);
}



/***********************************************************************
     * Map
     * checkInteraction

***********************************************************************/
fired::MapObject *fired::Map::checkInteraction(fired::Character *owner) {
	for (unsigned int i = 0; i < objects.size(); i++)
		if (objects[i]->decor->rect.intersects(owner->phys.rect)) return objects[i];

	return NULL;
}
