/***********************************************************************
     * File       : themap.cpp
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

	sky[0] = sf::Vertex(sf::Vector2f(0, 0), biome->skyHi);
	sky[1] = sf::Vertex(sf::Vector2f(0, 0), biome->skyHi);
	sky[2] = sf::Vertex(sf::Vector2f(0, 0), biome->skyLow);
	sky[3] = sf::Vertex(sf::Vector2f(0, 0), biome->skyLow);

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

	deleteList(decors);
	deleteList(objects);
}



/***********************************************************************
     * Map
     * update

***********************************************************************/
void fired::Map::update() {
	sf::Vector2f offset = cam->offset;
	resetLight();

	biome->bgSprite->setPosition(offset);
	biome->bgSprite->setTextureRect(sf::IntRect(offset.x / 3.0f, 0, settings->window.width, settings->window.height));

	sky[0].position.x = offset.x;
	sky[0].position.y = offset.y;

	sky[1].position.x = offset.x + settings->window.width;
	sky[1].position.y = offset.y;

	sky[2].position.x = offset.x + settings->window.width;
	sky[2].position.y = offset.y + settings->window.height;

	sky[3].position.x = offset.x;
	sky[3].position.y = offset.y + settings->window.height;

	render();
}



/***********************************************************************
     * Map
     * render

***********************************************************************/
void fired::Map::render() {
	app->draw(sky, 4, sf::Quads);
	app->draw(*biome->bgSprite);

	sf::Vector2i from((int)(cam->offset.x / TILE_SIZE), (int)(cam->offset.y / TILE_SIZE));
	sf::Vector2i to(from + visibleTiles);

	if (from.x < 0  ) from.x = 0;
	if (from.y < 0  ) from.y = 0;
	if (to.x > sizeX) to.x = sizeX;
	if (to.y > sizeY) to.y = sizeY;

	for (int i = from.x; i < to.x; i++)
		for (int j = from.y; j < to.y; j++)
			tiles[i][j].render();

	for (unsigned int i = 0; i < decors.size(); i++)
		decors[i]->render();

	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->render(this);
}



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
				tiles[i][j].intensity = LIGHT_MAX_LIGHTLEVEL;
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



/***********************************************************************
     * Map
     * spawn

***********************************************************************/
void fired::Map::spawn() {
	if (biome->creatures.size() == 0) return;

	int toSpawn = random() % biome->creatures.size();
	world->spawn(sf::Vector2f(2200 + random() % 200, 560), biome->creatures[toSpawn]);
}



/***********************************************************************
     * Map
     * isSolid

***********************************************************************/
bool inline fired::Map::isSolid(int i, int j) {
	if (i < 0)      return true;
	if (i >= sizeX) return true;
	if (j < 0)      return true;
	if (j >= sizeY) return true;

	return tiles[i][j].isWall;
}



/***********************************************************************
     * Map
     * isPlatform

***********************************************************************/
bool inline fired::Map::isPlatform(int i, int j, fired::Phys *phys) {
	if (i < 0)      return true;
	if (i >= sizeX) return true;
	if (j < 0)      return true;
	if (j >= sizeY) return true;

	if (!tiles[i][j].isPlatform) return false;
	if (phys->velocity.y < 0)    return false;

	if (phys->jumpdown) {
		if (phys->jumpdownLevel == 0) phys->jumpdownLevel = j;
		return false;
	}

	if (phys->jumpdownLevel == j) return false;
	return true;
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
	else if (tiles[i-1][j].tileset == tiles[i][j].tileset && tiles[i-1][j].isWall >= tiles[i][j].isWall) left = 1;

	if (i == sizeX - 1) right = 1;
	else if (tiles[i+1][j].tileset == tiles[i][j].tileset && tiles[i+1][j].isWall >= tiles[i][j].isWall) right = 1;

	if (j == 0) top = 1;
	else if (tiles[i][j-1].tileset == tiles[i][j].tileset && tiles[i][j-1].isWall >= tiles[i][j].isWall) top = 1;

	if (j == sizeY - 1) bottom = 1;
	else if (tiles[i][j+1].tileset == tiles[i][j].tileset && tiles[i][j+1].isWall >= tiles[i][j].isWall) bottom = 1;

	resultTile = left   * 1 +
	             right  * 2 +
	             top    * 4 +
	             bottom * 8;

	tiles[i][j].setTile(resultTile);
}



/***********************************************************************
     * Map
     * checkCollision

***********************************************************************/
void inline fired::Map::checkCollision(fired::Phys *phys, fired::Character *character, int tile_x, int tile_y) {
	sf::FloatRect intersection;

	if (phys->rect.intersects(sf::FloatRect(tile_x * TILE_SIZE, tile_y * TILE_SIZE, TILE_SIZE, TILE_SIZE), intersection)) {
		if (intersection.width > intersection.height) {
			if (phys->pos.y < tile_y * TILE_SIZE) {
				phys->pos.y -= intersection.height;
				if (character) if (phys->velocity.y > PHYS_SAFE_FALL) character->damage((phys->velocity.y - PHYS_SAFE_FALL) / 10.0f, sf::Vector2f(phys->size.x / 2, phys->size.y), 100.0);
				if (phys->velocity.y > 0.0) phys->velocity.y = 0.0;
				phys->onGround      = true;
				phys->jumpdownLevel = 0;
			} else {
				phys->pos.y += intersection.height;
				if (phys->velocity.y < 0.0) phys->velocity.y = 0.0;
			}
		} else {
			if (phys->pos.x < tile_x * TILE_SIZE) {
				phys->pos.x -= intersection.width;
				if (phys->velocity.x > 0.0) phys->velocity.x = 0.0;
				phys->isMoving = false;
			} else {
				phys->pos.x += intersection.width;
				if (phys->velocity.x < 0.0) phys->velocity.x = 0.0;
				phys->isMoving = false;
			}
		}

		phys->calculate();
	}
}



/***********************************************************************
     * Map
     * checkPhys

***********************************************************************/
void fired::Map::checkPhys(fired::Phys *phys, fired::Character *character, float tunnelTime) {
	if (character) if (character->dead) return;
	int i, j;

	phys->onGround = false;

	if (phys->velocity.x > PHYS_MAX_FALL) phys->velocity.x = PHYS_MAX_FALL;
	if (phys->velocity.y > PHYS_MAX_FALL) phys->velocity.y = PHYS_MAX_FALL;

	float frameLeft = frameClock;
	float frameChunk;
	float velocity = vLen(phys->velocity + phys->acceleration * frameClock);

	if (velocity == 0.0)
		frameChunk = frameClock;
	else
		frameChunk = tunnelTime / velocity;


	while (frameLeft > 0.0) {
		if (frameChunk > frameLeft) frameChunk = frameLeft;

		phys->velocity += phys->acceleration * frameChunk;
		phys->pos += phys->velocity * frameChunk;
		phys->calculate();

		sf::Vector2i  tiles_from(floor(phys->pos.x / TILE_SIZE), floor(phys->pos.y / TILE_SIZE));
		sf::Vector2i  tiles_to(floor((phys->pos.x + phys->size.x) / TILE_SIZE), floor((phys->pos.y + phys->size.y) / TILE_SIZE));


		for (i = tiles_from.x + 1; i <= tiles_to.x - 1; i++) {
			if (isSolid(i, tiles_from.y)) checkCollision(phys, character, i, tiles_from.y);
			if (isSolid(i, tiles_to.y  )) checkCollision(phys, character, i, tiles_to.y  );
			if (isPlatform(i, tiles_to.y, phys)) checkCollision(phys, character, i, tiles_to.y  );
		}

		for (j = tiles_from.y + 1; j <= tiles_to.y - 1; j++) {
			if (isSolid(tiles_from.x, j)) checkCollision(phys, character, tiles_from.x, j);
			if (isSolid(tiles_to.x  , j)) checkCollision(phys, character, tiles_to.x  , j);
		}

		if (phys->velocity.x > 0) {
			if (isSolid(tiles_from.x, tiles_from.y)) checkCollision(phys, character, tiles_from.x, tiles_from.y);
			if (isSolid(tiles_from.x, tiles_to.y  )) checkCollision(phys, character, tiles_from.x, tiles_to.y  );
			if (isPlatform(tiles_from.x, tiles_to.y, phys)) checkCollision(phys, character, tiles_from.x, tiles_to.y  );

			if (isSolid(tiles_to.x  , tiles_from.y)) checkCollision(phys, character, tiles_to.x  , tiles_from.y);
			if (isSolid(tiles_to.x  , tiles_to.y  )) checkCollision(phys, character, tiles_to.x  , tiles_to.y  );
			if (isPlatform(tiles_to.x, tiles_to.y, phys)) checkCollision(phys, character, tiles_to.x, tiles_to.y  );
		} else {
			if (isSolid(tiles_to.x  , tiles_from.y)) checkCollision(phys, character, tiles_to.x  , tiles_from.y);
			if (isSolid(tiles_to.x  , tiles_to.y  )) checkCollision(phys, character, tiles_to.x  , tiles_to.y  );
			if (isPlatform(tiles_to.x, tiles_to.y, phys)) checkCollision(phys, character, tiles_to.x, tiles_to.y  );

			if (isSolid(tiles_from.x, tiles_from.y)) checkCollision(phys, character, tiles_from.x, tiles_from.y);
			if (isSolid(tiles_from.x, tiles_to.y  )) checkCollision(phys, character, tiles_from.x, tiles_to.y  );
			if (isPlatform(tiles_from.x, tiles_to.y, phys)) checkCollision(phys, character, tiles_from.x, tiles_to.y  );
		}

		frameLeft -= frameChunk;
	}
}



/***********************************************************************
     * Map
     * checkShot

***********************************************************************/
bool fired::Map::checkShot(fired::Shot *shot) {
	sf::Vector2f dir(shot->velocity * frameClock);
	sf::FloatRect ray(shot->pos, dir);
	sf::IntRect tilesToCheck(shot->pos.x / TILE_SIZE, shot->pos.y / TILE_SIZE, (shot->pos + dir).x / TILE_SIZE, (shot->pos + dir).y / TILE_SIZE);

	sf::Vector2f c, n;
	float dist;

	if (dir.x < 0) std::swap(tilesToCheck.left, tilesToCheck.width);
	if (dir.y < 0) std::swap(tilesToCheck.top, tilesToCheck.height);

	for (int i = tilesToCheck.left; i <= tilesToCheck.width; i++)
	for (int j = tilesToCheck.top; j <= tilesToCheck.height; j++)
	if (isSolid(i, j))
		if (lineBoxCollision(sf::FloatRect(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE), ray, &c, &n, &dist)) {
			n *= 200.0f;
			world->addBulletSplash(c, n);
			return true;
		}

	return false;
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
