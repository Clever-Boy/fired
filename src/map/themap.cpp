#include <stdio.h>
#include "game.hpp"

//======================================================================


void fired::Map::init(fired::Game *_game, fired::Camera *_cam) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	cam      = _cam;

	bgTex    = new sf::Texture();
	bgSprite = new sf::RectangleShape();

	bgTex->loadFromFile("data/img/world/bg/sky.jpg");
	bgSprite->setTexture(bgTex);
	bgTex->setRepeated(true);
	bgSprite->setSize(sf::Vector2f(settings->window.width, settings->window.height));

	tilesets.push_back(NULL);

	tilesets.push_back(new fired::Tileset);
	tilesets.back()->init("data/img/world/tilesets/grass.tga");

	tilesets.push_back(new fired::Tileset);
	tilesets.back()->init("data/img/world/tilesets/dirt.tga");

	visibleTiles.x = settings->window.width  / TILE_SIZE + 2;
	visibleTiles.y = settings->window.height / TILE_SIZE + 2;

	load("data/maps/test.map");
}

//======================================================================


void fired::Map::deinit() {
	for (int i = 0; i < sizeX; i++)
		delete tiles[i];

	delete tiles;


	for (int i = 1; i < tilesets.size(); i++) {
		tilesets[i]->deinit();
		delete tilesets[i];
	}

	tilesets.clear();
}

//======================================================================


void fired::Map::update() {
	sf::Vector2f offset = cam->getOffset();

	bgSprite->setPosition(offset);
	bgSprite->setTextureRect(sf::IntRect(offset.x / 2, offset.y / 2, settings->window.width, settings->window.height));

	render();
}

//======================================================================


void fired::Map::render() {
	app->draw(*bgSprite);

	sf::Vector2i from((int)(cam->getOffset().x / TILE_SIZE), (int)(cam->getOffset().y / TILE_SIZE));
	sf::Vector2i to(from + visibleTiles);

	if (from.x < 0  ) from.x = 0;
	if (from.y < 0  ) from.y = 0;
	if (to.x > sizeX) to.x = sizeX;
	if (to.y > sizeY) to.y = sizeY;

	for (int i = from.x; i < to.x; i++)
		for (int j = from.y; j < to.y; j++)
			tiles[i][j].render(app);
}

//======================================================================


void fired::Map::load(const char* filename) {
	FILE *fp;
	fired::MapTile tile;


	if ((fp = fopen(filename, "r")) == NULL) return;
	fread(&sizeX, sizeof(int), 1, fp);
	fread(&sizeY, sizeof(int), 1, fp);
	mapSize = sf::Vector2i(sizeX * TILE_SIZE, sizeY * TILE_SIZE);

	tiles = new fired::Tile*[sizeX];
	for (int i = 0; i < sizeX; i++)
		tiles[i] = new fired::Tile[sizeY];

	for (int i = 0; i < sizeX; i++)
		for (int j = 0; j < sizeY; j++) {
			fread(&tile, sizeof(tile), 1, fp);
			tiles[i][j].init(tile.tileset, i, j);
		}

	findTiles();

	fclose(fp);
	for (int i = 0; i < sizeX; i++) for (int j = 0; j < sizeY; j++)
		tiles[i][j].setTileset(tilesets[tiles[i][j].getIndex()]);
}

//======================================================================


void fired::Map::save(const char* filename) {
	FILE *fp;
	fired::MapTile tile;


	if ((fp = fopen(filename, "w")) == NULL) return;
	fwrite(&sizeX, sizeof(int), 1, fp);
	fwrite(&sizeY, sizeof(int), 1, fp);

	for (int i = 0; i < sizeX; i++)
		for (int j = 0; j < sizeY; j++) {
			tile.tileset = tiles[i][j].getIndex();
			fwrite(&tile, sizeof(tile), 1, fp);
		}

	fclose(fp);
}

//======================================================================

void fired::Map::findTiles() {
	for (int i = 0; i < sizeX; i++) for (int j = 0; j < sizeY; j++) 
		findTile(i, j);
}


//======================================================================

void fired::Map::findTile(int i, int j) {
	int resultTile;
	int top    = 0;
	int left   = 0;
	int right  = 0;
	int bottom = 0;

	if (i == 0) left = 1;
	else if (tiles[i-1][j].getIndex() == tiles[i][j].getIndex()) left = 1;

	if (i == sizeX - 1) right = 1;
	else if (tiles[i+1][j].getIndex() == tiles[i][j].getIndex()) right = 1;

	if (j == 0) top = 1;
	else if (tiles[i][j-1].getIndex() == tiles[i][j].getIndex()) top = 1;

	if (j == sizeY - 1) bottom = 1;
	else if (tiles[i][j+1].getIndex() == tiles[i][j].getIndex()) bottom = 1;

	resultTile = left   * 1 +
	             right  * 2 +
	             top    * 4 +
	             bottom * 8;

	tiles[i][j].setTile(resultTile);
}


//======================================================================


void checkCollision(fired::Phys *phys, int tile_x, int tile_y) {
	sf::FloatRect intersection;

	if (phys->rect.intersects(sf::FloatRect(tile_x * TILE_SIZE, tile_y * TILE_SIZE, TILE_SIZE, TILE_SIZE), intersection)) {
		if (intersection.width > intersection.height) {
			if (phys->pos.y < tile_y * TILE_SIZE) {
				phys->pos.y -= intersection.height;
				if (phys->velocity.y > 0.0) phys->velocity.y = 0.0;
				phys->onGround = true;
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

		phys->center = phys->pos + sf::Vector2f(phys->size.x / 2, phys->size.y / 2);
		phys->rect   = sf::FloatRect(phys->pos, phys->size);
	}
}

//======================================================================


bool fired::Map::isSolid(int i, int j) {
	if (i < 0)      return true;
	if (i >= sizeX) return true;
	if (j < 0)      return true;
	if (j >= sizeY) return true;

	return tiles[i][j].isSolid();
}

//======================================================================


void fired::Map::checkPhys(fired::Phys *phys) {
	int i, j;

	phys->onGround = false;

	if (phys->velocity.x > PHYS_MAX_FALL) phys->velocity.x = PHYS_MAX_FALL;
	if (phys->velocity.y > PHYS_MAX_FALL) phys->velocity.y = PHYS_MAX_FALL;

	float frameLeft = frameClock;
	float frameChunk;
	float velocity = sqrt(sqr(phys->velocity.x + phys->acceleration.x * frameClock) + sqr(phys->velocity.y + phys->acceleration.y * frameClock));

	if (velocity == 0.0)
		frameChunk = frameClock;
	else
		frameChunk = PHYS_TUNNEL_CHUNK / velocity;


	while (frameLeft > 0.0) {
		if (frameChunk > frameLeft) frameChunk = frameLeft;

		phys->velocity += phys->acceleration * frameChunk;
		phys->pos += phys->velocity * frameChunk;
		phys->rect = sf::FloatRect(phys->pos, phys->size);
		phys->center = phys->pos + sf::Vector2f(phys->size.x / 2, phys->size.y / 2);

		sf::Vector2i  tiles_from(floor(phys->pos.x / TILE_SIZE), floor(phys->pos.y / TILE_SIZE));
		sf::Vector2i  tiles_to(floor((phys->pos.x + phys->size.x) / TILE_SIZE), floor((phys->pos.y + phys->size.y) / TILE_SIZE));


		for (i = tiles_from.x + 1; i <= tiles_to.x - 1; i++) {
			if (isSolid(i, tiles_from.y)) checkCollision(phys, i, tiles_from.y);
			if (isSolid(i, tiles_to.y  )) checkCollision(phys, i, tiles_to.y);
		}

		for (j = tiles_from.y + 1; j <= tiles_to.y - 1; j++) {
			if (isSolid(tiles_from.x, j)) checkCollision(phys, tiles_from.x, j);
			if (isSolid(tiles_to.x  , j)) checkCollision(phys, tiles_to.x, j);
		}

		if (phys->velocity.x > 0) {
			if (isSolid(tiles_from.x, tiles_from.y)) checkCollision(phys, tiles_from.x, tiles_from.y);
			if (isSolid(tiles_from.x, tiles_to.y  )) checkCollision(phys, tiles_from.x, tiles_to.y  );
			if (isSolid(tiles_to.x  , tiles_from.y)) checkCollision(phys, tiles_to.x  , tiles_from.y);
			if (isSolid(tiles_to.x  , tiles_to.y  )) checkCollision(phys, tiles_to.x  , tiles_to.y  );
		} else {
			if (isSolid(tiles_to.x  , tiles_from.y)) checkCollision(phys, tiles_to.x  , tiles_from.y);
			if (isSolid(tiles_to.x  , tiles_to.y  )) checkCollision(phys, tiles_to.x  , tiles_to.y  );
			if (isSolid(tiles_from.x, tiles_from.y)) checkCollision(phys, tiles_from.x, tiles_from.y);
			if (isSolid(tiles_from.x, tiles_to.y  )) checkCollision(phys, tiles_from.x, tiles_to.y  );
		}

		frameLeft -= frameChunk;
	}
}
