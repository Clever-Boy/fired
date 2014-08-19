/***********************************************************************
     * File       : map_lighting.cpp
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

	color = applyIntensity(color, intensity);
	tiles[index.x][index.y].light = mixColors(tiles[index.x][index.y].light, color);

	if (tiles[index.x][index.y].intensity < intensity)
		tiles[index.x][index.y].intensity = intensity;
}



/***********************************************************************
     * Map
     * initIntensity

***********************************************************************/
void fired::Map::initIntensity(fired::Tile *tile) {
	int index = tile->intensity - 1;
	if (index < 0 || index >= LIGHT_MAX_LIGHTLEVEL) return;

	lightTiles[index][lightCounts[index]++] = tile;
}



/***********************************************************************
     * Map
     * setIntensity

***********************************************************************/
void fired::Map::setIntensity(fired::Tile *tile, char intensity, sf::Color color) {
	if (canMixColors(tile->light, color) || intensity > tile->intensity) {
		tile->light = mixColors(tile->light, color);

		if (intensity != tile->intensity) {
			tile->intensity = intensity;
			initIntensity(tile);
		}
	}
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
     * addExplosion

***********************************************************************/
void fired::Map::addExplosion(sf::Vector2f pos, float radius, float lifetime) {
	sf::Vector2f tile;
	sf::Vector2i from((int)((pos.x - radius) / TILE_SIZE), (int)((pos.y - radius) / TILE_SIZE));
	sf::Vector2i to((int)((pos.x + radius) / TILE_SIZE), (int)((pos.y + radius) / TILE_SIZE));

	float len;

	if (from.x < 0) from.x = 0;
	if (from.y < 0) from.y = 0;
	if (to.x >= sizeX) to.x = sizeX - 1;
	if (to.y >= sizeX) to.y = sizeY - 1;

	for (int x = from.x; x <= to.x; x++) for (int y = from.y; y <= to.y; y++) {
		tile = getTilePos(x, y);
		len = sqrt(sqr(pos.x - tile.x) + sqr(pos.y - tile.y));

		if (len <= radius)
			addTemporaryLightSource(tile, LIGHT_MAX_LIGHTLEVEL, sf::Color::White, lifetime * (2.0f * radius - len) / (2.0f * radius));
	}
}



/***********************************************************************
     * Map
     * checkNeighbours

***********************************************************************/
void fired::Map::checkNeighbours(fired::Tile *tile) {
	int x = tile->index.x;
	int y = tile->index.y;

	char intensity = tile->intensity - tile->absorb;
	if (intensity < 0) return;
	sf::Color color = reapplyIntensity(tile->light, tile->intensity, intensity);

	if (x > 0)         setIntensity(&tiles[x-1][y], intensity, color);
	if (x < sizeX - 1) setIntensity(&tiles[x+1][y], intensity, color);
	if (y > 0)         setIntensity(&tiles[x][y-1], intensity, color);
	if (y < sizeY - 1) setIntensity(&tiles[x][y+1], intensity, color);


	color.r *= 0.9f;
	color.g *= 0.9f;
	color.b *= 0.9f;

	if (x > 0         && y < sizeY - 1) setIntensity(&tiles[x-1][y+1], intensity, color);
	if (x < sizeX - 1 && y > 0)         setIntensity(&tiles[x+1][y-1], intensity, color);
	if (y > 0         && x > 0)         setIntensity(&tiles[x-1][y-1], intensity, color);
	if (y < sizeY - 1 && x < sizeX - 1) setIntensity(&tiles[x+1][y+1], intensity, color);
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

	sf::Color color = applyIntensity(biome->lightness, biome->intensity);

	for (int i = 0; i < LIGHT_MAX_LIGHTLEVEL; lightCounts[i++] = 0);
	for (int i = from.x; i < to.x; i++)
		for (int j = from.y; j < to.y; j++)
			if (!tiles[i][j].tileset) {
				tiles[i][j].intensity = biome->intensity;
				tiles[i][j].light     = color;
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
			initIntensity(&tiles[i][j]);

	for (int i = LIGHT_MAX_LIGHTLEVEL - 1; i >= 0; i--)
		for (int j = 0; j < lightCounts[i]; j++) {
			if (lightTiles[i][j]->intensity != i + 1) continue;
			checkNeighbours(lightTiles[i][j]);
		}
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
