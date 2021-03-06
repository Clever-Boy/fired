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

	bgTex    = new sf::Texture();
	bgSprite = new sf::RectangleShape();

	bgTex->loadFromFile(biome->background);
	bgSprite->setTexture(bgTex);
	bgTex->setRepeated(true);
	bgTex->setSmooth(true);
	bgSprite->setSize(sf::Vector2f(settings->window.width, settings->window.height));

	bgScale = (float)bgTex->getSize().y / (float)settings->window.height;

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
	delete bgSprite;
	delete bgTex;

	deleteList(objects);
	deleteList(lights);
	deleteList(spawns);
}



/***********************************************************************
     * Map
     * update

***********************************************************************/
void fired::Map::update() {
	sf::Vector2f offset = cam->offset;
	resetLight();

	bgSprite->setPosition(offset);
	bgSprite->setTextureRect(sf::IntRect(offset.x / 3.0f, 0, settings->window.width * bgScale, bgTex->getSize().y));

	render();
}



/***********************************************************************
     * Map
     * render

***********************************************************************/
void fired::Map::render() {
	app->draw(*bgSprite);
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
void fired::Map::spawn(sf::Vector2f position, fired::MapSpawnType type) {
	if (spawns.size() == 0) return;

	fired::BaseCreature *toSpawn;
	switch (type) {
		case mstCreature:
			if (biome->creatures.size() == 0) return;
			toSpawn = biome->creatures[rand() % biome->creatures.size()];
			break;

		case mstCritter:
			if (biome->critters.size() == 0) return;
			toSpawn = biome->critters[rand() % biome->critters.size()];
			break;

		case mstBoss:
			if (biome->bosses.size() == 0) return;
			toSpawn = biome->bosses[rand() % biome->bosses.size()];
			break;
	}

	int   place = -1;
	float minDist;
	float dist;

	sf::Vector2f pos;
	sf::IntRect  spawnRect;

	for (unsigned int i = 0; i < spawns.size(); i++) {
		if (!(spawns[i]->type & type)) continue;
		if (cam->isRectVisible(sf::FloatRect(spawns[i]->spawn))) continue;

		dist = vLen(position - rectCenter(spawns[i]->spawn));
		if ((place == -1) || (dist < minDist)) {
			place = i;
			minDist = dist;
		}
	}

	if (place == -1) return;

	spawnRect = getRectToSpawn(toSpawn, spawns[place]->spawn);
	pos       = sf::Vector2f(spawnRect.left + rand() % spawnRect.width, spawnRect.top + spawnRect.height);

	world->spawn(pos, toSpawn, type);
}



/***********************************************************************
     * Map
     * spawn

***********************************************************************/
sf::Vector2f fired::Map::getPlayerSpawn() {
	sf::IntRect spawnRect = getRectToSpawn(container->getCreature("Player"), startRect);
	return sf::Vector2f(spawnRect.left + rand() % spawnRect.width, spawnRect.top + spawnRect.height);
}



/***********************************************************************
     * Map
     * spawn

***********************************************************************/
sf::IntRect fired::Map::getRectToSpawn(fired::BaseCreature *creature, sf::IntRect spawnRect) {
	sf::IntRect result(spawnRect);
	sf::Vector2i size = sf::Vector2i(creature->model->size * creature->modelScale);

	result.width  -= size.x;
	result.height -= size.y;
	return result;
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
	int resultTileBack;

	if (tiles[i][j].tileset == 0) return;

	int top    = 0;
	int left   = 0;
	int right  = 0;
	int bottom = 0;

	int topBack    = 0;
	int leftBack   = 0;
	int rightBack  = 0;
	int bottomBack = 0;


	if (i == 0) left = 1;
	else if (tiles[i-1][j].tileset && tiles[i-1][j].isWall >= tiles[i][j].isWall) left = 1;

	if (i == sizeX - 1) right = 1;
	else if (tiles[i+1][j].tileset && tiles[i+1][j].isWall >= tiles[i][j].isWall) right = 1;

	if (j == 0) top = 1;
	else if (tiles[i][j-1].tileset && tiles[i][j-1].isWall >= tiles[i][j].isWall) top = 1;

	if (j == sizeY - 1) bottom = 1;
	else if (tiles[i][j+1].tileset && tiles[i][j+1].isWall >= tiles[i][j].isWall) bottom = 1;


	if (i == 0) leftBack = 1;
	else if (tiles[i-1][j].tileset) leftBack = 1;

	if (i == sizeX - 1) rightBack = 1;
	else if (tiles[i+1][j].tileset) rightBack = 1;

	if (j == 0) topBack = 1;
	else if (tiles[i][j-1].tileset) topBack = 1;

	if (j == sizeY - 1) bottomBack = 1;
	else if (tiles[i][j+1].tileset) bottomBack = 1;


	resultTile = left   * 1 +
	             right  * 2 +
	             top    * 4 +
	             bottom * 8;

	resultTileBack = leftBack   * 1 +
	                 rightBack  * 2 +
	                 topBack    * 4 +
	                 bottomBack * 8;


	tiles[i][j].setTile(resultTile);
	tiles[i][j].setTileBack(resultTileBack);
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
