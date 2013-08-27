#include "game.hpp"

//======================================================================


fired::Map::Map(fired::Camera *_cam, fired::World *_world) {
	cam      = _cam;
	world    = _world;

	bgTex    = new sf::Texture();
	bgSprite = new sf::RectangleShape();
	tileset  = new fired::Tileset();

	bgTex->loadFromFile("data/img/world/bg/sky.jpg");
	bgSprite->setTexture(bgTex);
	bgTex->setRepeated(true);
	bgTex->setSmooth(true);
	bgSprite->setSize(sf::Vector2f(settings->window.width, settings->window.height));

	visibleTiles.x = settings->window.width  / TILE_SIZE + 2;
	visibleTiles.y = settings->window.height / TILE_SIZE + 2;

	mapLoad(this, "data/maps/test.map");
}

//======================================================================


fired::Map::~Map() {
	for (int i = 0; i < sizeX; delete tiles[i++]);

	delete tiles;
	delete tileset;
	deleteList(decors);
	deleteList(objects);
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
			tiles[i][j].render();

	for (unsigned int i = 0; i < decors.size(); i++)
		decors[i]->render();

	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->render();
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


void fired::Map::findTile(int i, int j) {
	int resultTile;
	int top    = 0;
	int left   = 0;
	int right  = 0;
	int bottom = 0;

	if (i == 0) left = 1;
	else if (tiles[i-1][j].getIndex() == tiles[i][j].getIndex() && tiles[i-1][j].isSolid() >= tiles[i][j].isSolid()) left = 1;

	if (i == sizeX - 1) right = 1;
	else if (tiles[i+1][j].getIndex() == tiles[i][j].getIndex() && tiles[i+1][j].isSolid() >= tiles[i][j].isSolid()) right = 1;

	if (j == 0) top = 1;
	else if (tiles[i][j-1].getIndex() == tiles[i][j].getIndex() && tiles[i][j-1].isSolid() >= tiles[i][j].isSolid()) top = 1;

	if (j == sizeY - 1) bottom = 1;
	else if (tiles[i][j+1].getIndex() == tiles[i][j].getIndex() && tiles[i][j+1].isSolid() >= tiles[i][j].isSolid()) bottom = 1;

	resultTile = left   * 1 +
	             right  * 2 +
	             top    * 4 +
	             bottom * 8;

	tiles[i][j].setTile(resultTile);
}

//======================================================================


void fired::Map::checkCollision(fired::Phys *phys, fired::Character *character, int tile_x, int tile_y) {
	sf::FloatRect intersection;

	if (phys->rect.intersects(sf::FloatRect(tile_x * TILE_SIZE, tile_y * TILE_SIZE, TILE_SIZE, TILE_SIZE), intersection)) {
		if (intersection.width > intersection.height) {
			if (phys->pos.y < tile_y * TILE_SIZE) {
				phys->pos.y -= intersection.height;
				if (character) if (phys->velocity.y > PHYS_SAFE_FALL) character->damage((phys->velocity.y - PHYS_SAFE_FALL) / 10.0f, false, sf::Vector2f(phys->size.x / 2, phys->size.y), 100.0);
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

		phys->calculate();
	}
}

//======================================================================


void fired::Map::checkPhys(fired::Phys *phys, fired::Character *character) {
	if (character) if (character->isDead()) return;
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
		frameChunk = PHYS_TUNNEL_TIME / velocity;


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
		}

		for (j = tiles_from.y + 1; j <= tiles_to.y - 1; j++) {
			if (isSolid(tiles_from.x, j)) checkCollision(phys, character, tiles_from.x, j);
			if (isSolid(tiles_to.x  , j)) checkCollision(phys, character, tiles_to.x  , j);
		}

		if (phys->velocity.x > 0) {
			if (isSolid(tiles_from.x, tiles_from.y)) checkCollision(phys, character, tiles_from.x, tiles_from.y);
			if (isSolid(tiles_from.x, tiles_to.y  )) checkCollision(phys, character, tiles_from.x, tiles_to.y  );
			if (isSolid(tiles_to.x  , tiles_from.y)) checkCollision(phys, character, tiles_to.x  , tiles_from.y);
			if (isSolid(tiles_to.x  , tiles_to.y  )) checkCollision(phys, character, tiles_to.x  , tiles_to.y  );
		} else {
			if (isSolid(tiles_to.x  , tiles_from.y)) checkCollision(phys, character, tiles_to.x  , tiles_from.y);
			if (isSolid(tiles_to.x  , tiles_to.y  )) checkCollision(phys, character, tiles_to.x  , tiles_to.y  );
			if (isSolid(tiles_from.x, tiles_from.y)) checkCollision(phys, character, tiles_from.x, tiles_from.y);
			if (isSolid(tiles_from.x, tiles_to.y  )) checkCollision(phys, character, tiles_from.x, tiles_to.y  );
		}

		frameLeft -= frameChunk;
	}
}

//======================================================================


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


//======================================================================

fired::MapObject *fired::Map::checkInteraction(fired::Character *owner) {
	for (unsigned int i = 0; i < objects.size(); i++)
		if (objects[i]->decor->rect.intersects(owner->phys.rect)) return objects[i];

	return NULL;
}
