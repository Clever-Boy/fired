/***********************************************************************
     * File       : physics.cpp
     * Created    : Feb 04, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



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
			addTemporaryLightSource(c, LIGHT_SHOT_INTENSITY, sf::Color::White, LIGHT_SHOT_LIFETIME);
			return true;
		}

	return false;
}
