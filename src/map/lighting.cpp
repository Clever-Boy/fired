/***********************************************************************
     * File       : lighting.cpp
     * Created    : Feb 04, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Map
     * setIntensity

***********************************************************************/
void fired::Map::setIntensity(fired::Tile *tile, char intensity) {
	sf::Uint8 color = getColor(intensity);
	tile->intensity = intensity;
	tile->light = sf::Color(color, color, color);

	int index = intensity - 1;

	if (index < 0) return;
	if (index >= LIGHT_MAX_LIGHTLEVEL) return;

	lightTiles[index][lightCounts[index]] = tile;
	lightCounts[index]++;
}



/***********************************************************************
     * Map
     * addLightSource

***********************************************************************/
void fired::Map::addLightSource(int x, int y, char intensity) {
	setIntensity(&tiles[x][y], intensity);
}



/***********************************************************************
     * Map
     * addTemporaryLightSource

***********************************************************************/
void fired::Map::addTemporaryLightSource(sf::Vector2f pos, char intensity, sf::Color color, float lifetime) {
	lights.push_back(new fired::TemporaryLightSource(intensity, lifetime, pos, color, this));
}



/***********************************************************************
     * Map
     * checkNeighbours

***********************************************************************/
void fired::Map::checkNeighbours(fired::Tile *tile) {
	int x = tile->index.x;
	int y = tile->index.y;
	char intensity = tile->intensity - tile->absorb;

	if (x > 0)
		if (tiles[x-1][y].intensity < intensity)
			setIntensity(&tiles[x-1][y], intensity);

	if (x < sizeX - 1)
		if (tiles[x+1][y].intensity < intensity)
			setIntensity(&tiles[x+1][y], intensity);

	if (y > 0)
		if (tiles[x][y-1].intensity < intensity)
			setIntensity(&tiles[x][y-1], intensity);

	if (y < sizeY - 1)
		if (tiles[x][y+1].intensity < intensity)
			setIntensity(&tiles[x][y+1], intensity);
}



/***********************************************************************
     * Map
     * light

***********************************************************************/
void fired::Map::light() {
	buildLight();
	renderLight();
}



/***********************************************************************
     * Map
     * resetLight

***********************************************************************/
void fired::Map::resetLight() {
	sf::Vector2i from((int)(cam->offset.x / TILE_SIZE) - LIGHT_OFFSCREEN_TILES, (int)(cam->offset.y / TILE_SIZE) - LIGHT_OFFSCREEN_TILES);
	sf::Vector2i to(from + visibleTiles + sf::Vector2i(LIGHT_OFFSCREEN_TILES * 2, LIGHT_OFFSCREEN_TILES * 2));

	if (from.x < 0) from.x = 0;
	if (from.y < 0) from.y = 0;
	if (to.x > sizeX) to.x = sizeX;
	if (to.y > sizeY) to.y = sizeY;

	for (int i = 0; i < LIGHT_MAX_LIGHTLEVEL; lightCounts[i++] = 0);
	for (int i = from.x; i < to.x; i++)
		for (int j = from.y; j < to.y; j++)
			if (!tiles[i][j].tileset)
				tiles[i][j].intensity = biome->intensity;
			else
				tiles[i][j].intensity = 0;
}



/***********************************************************************
     * Map
     * buildLight

***********************************************************************/
void fired::Map::buildLight() {
	sf::Vector2i from((int)(cam->offset.x / TILE_SIZE) - LIGHT_OFFSCREEN_TILES + 1, (int)(cam->offset.y / TILE_SIZE) - LIGHT_OFFSCREEN_TILES + 1);
	sf::Vector2i to(from + visibleTiles + sf::Vector2i(LIGHT_OFFSCREEN_TILES * 2 - 2, LIGHT_OFFSCREEN_TILES * 2 - 2));

	if (from.x < 0) from.x = 0;
	if (from.y < 0) from.y = 0;
	if (to.x > sizeX) to.x = sizeX;
	if (to.y > sizeY) to.y = sizeY;

	for (int i = from.x; i < to.x; i++)
		for (int j = from.y; j < to.y; j++)
			setIntensity(&tiles[i][j], tiles[i][j].intensity);

	for (int i = LIGHT_MAX_LIGHTLEVEL - 1; i >= 0; i--)
		for (int j = 0; j < lightCounts[i]; j++) {
			if (lightTiles[i][j]->intensity != i + 1) continue;
			checkNeighbours(lightTiles[i][j]);
		}
}



/***********************************************************************
     * Map
     * getColor

***********************************************************************/
sf::Uint8 fired::Map::getColor(char intensity) {
	if (intensity > LIGHT_ABSOLUTE) return 255;
	else if (intensity <= 0) return 0;
	else return ((float)intensity / LIGHT_ABSOLUTE) * 255;
}



/***********************************************************************
     * Map
     * getTilePos

***********************************************************************/
sf::Vector2f fired::Map::getTilePos(int x, int y) {
	return sf::Vector2f(TILE_SIZE / 2.0f + TILE_SIZE * x, TILE_SIZE / 2.0f + TILE_SIZE * y);
}



/***********************************************************************
     * Map
     * getTileColor

***********************************************************************/
sf::Color fired::Map::getTileLight(int x, int y) {
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x >= sizeX) x = sizeX - 1;
	if (y >= sizeY) y = sizeY - 1;

	return tiles[x][y].light;
}



/***********************************************************************
     * Map
     * renderLight

***********************************************************************/
void fired::Map::renderLight() {
	sf::Vector2i from = sf::Vector2i((int)(cam->offset.x / TILE_SIZE), (int)(cam->offset.y / TILE_SIZE));
	sf::Vector2i to = sf::Vector2i(from + visibleTiles);

	if (from.x < 0) from.x = 0;
	if (from.y < 0) from.y = 0;
	if (to.x > sizeX) to.x = sizeX;
	if (to.y > sizeY) to.y = sizeY;

	sf::Vector2f offset((int)(cam->offset.x) % (int)TILE_SIZE, (int)(cam->offset.y) % (int)TILE_SIZE);
	sf::Vector2f tileCenter(TILE_SIZE / 2.0f, TILE_SIZE / 2.0f);

	for (int i = from.x - 1; i < to.x; i++)
		for (int j = from.y - 1; j < to.y; j++) {
			lightMask[0].position = getTilePos(i  , j  );
			lightMask[1].position = getTilePos(i+1, j  );
			lightMask[2].position = getTilePos(i+1, j+1);
			lightMask[3].position = getTilePos(i  , j+1);

			lightMask[0].color = getTileLight(i  , j  );
			lightMask[1].color = getTileLight(i+1, j  );
			lightMask[2].color = getTileLight(i+1, j+1);
			lightMask[3].color = getTileLight(i  , j+1);

			app->draw(lightMask, 4, sf::Quads, sf::BlendMultiply);
		}
}
