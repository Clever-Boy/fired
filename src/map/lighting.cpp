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
     * addIntensity

***********************************************************************/
void fired::Map::addIntensity(sf::Vector2i index, char intensity, sf::Color color) {
	if (index.x < 0 || index.x >= sizeX || index.y < 0 || index.y >= sizeY)
		return;

	float k;
	if (intensity >= LIGHT_ABSOLUTE) k = 1.0f;
	else                             k = (float)intensity / (float)LIGHT_ABSOLUTE;

	color.r = (char)(color.r * k);
	color.g = (char)(color.g * k);
	color.b = (char)(color.b * k);
	color.a = 255;

	tiles[index.x][index.y].light = mixColors(tiles[index.x][index.y].light, color);

	if (tiles[index.x][index.y].intensity < intensity)
		tiles[index.x][index.y].intensity = intensity;
}



/***********************************************************************
     * Map
     * initIntensity

***********************************************************************/
void fired::Map::initIntensity(fired::Tile *tile, char intensity, sf::Color color) {
	float k;
	if (intensity >= LIGHT_ABSOLUTE) k = 1.0f;
	else                             k = (float)intensity / (float)LIGHT_ABSOLUTE;

	color.r = (char)(color.r * k);
	color.g = (char)(color.g * k);
	color.b = (char)(color.b * k);
	color.a = 255;

	tile->intensity = intensity;
	tile->light = color;

	int index = intensity - 1;

	if (index < 0) return;
	if (index >= LIGHT_MAX_LIGHTLEVEL) return;

	lightTiles[index][lightCounts[index]] = tile;
	lightCounts[index]++;
}



/***********************************************************************
     * Map
     * setIntensity

***********************************************************************/
void fired::Map::setIntensity(fired::Tile *tile, char intensity, sf::Color color) {
	if (canMixColors(tile->light, color) || intensity > tile->intensity) {
	tile->intensity = intensity;
		int index = intensity - 1;

		if (index < 0) return;
		if (index >= LIGHT_MAX_LIGHTLEVEL) return;

		lightTiles[index][lightCounts[index]] = tile;
		lightCounts[index]++;
	}

	tile->light = mixColors(tile->light, color);
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
	float k;

	char intensity = tile->intensity - tile->absorb;
	if (intensity < 0) return;

	if (intensity > LIGHT_ABSOLUTE)             k = 1.0f;
	else if (tile->intensity >= LIGHT_ABSOLUTE) k = (float)intensity / (float)LIGHT_ABSOLUTE;
	else                                        k = (float)intensity / (float)tile->intensity;

	sf::Color color;
	color.r = (char)(tile->light.r * k);
	color.g = (char)(tile->light.g * k);
	color.b = (char)(tile->light.b * k);
	color.a = 255;

	if (x > 0)         setIntensity(&tiles[x-1][y], intensity, color);
	if (x < sizeX - 1) setIntensity(&tiles[x+1][y], intensity, color);
	if (y > 0)         setIntensity(&tiles[x][y-1], intensity, color);
	if (y < sizeY - 1) setIntensity(&tiles[x][y+1], intensity, color);
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
			if (!tiles[i][j].tileset) {
				tiles[i][j].intensity = biome->intensity;
				tiles[i][j].light     = biome->lightness;
			} else {
				tiles[i][j].intensity = 0;
				tiles[i][j].light     = sf::Color::Black;
			}
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
			initIntensity(&tiles[i][j], tiles[i][j].intensity, tiles[i][j].light);

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
