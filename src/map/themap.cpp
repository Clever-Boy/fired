#include "game.hpp"


void fired::Map::init(fired::Game *_game) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	bgTex    = new sf::Texture();
	bgSprite = new sf::RectangleShape();

	bgTex->loadFromFile("data/img/bg/sky.jpg");
	bgSprite->setTexture(bgTex);
	bgTex->setRepeated(true);
	bgSprite->setSize(sf::Vector2f(settings->window.width, settings->window.height));

	tileset.init("data/img/tilesets/dirt.tga");

	for (int i = 0; i < 50; i++) for (int j = 0; j < 38; j++) {
		tiles[i][j].init(NULL, i, j);
	}

	// Test map generation
	for (int i = 0; i < 50; i++)
		for (int j = 30; j < 38; j++)
			tiles[i][j].init(&tileset, i, j);

	for (int i = 17; i < 30; i+=2)
		tiles[i][29].init(&tileset, i, 29);
}



void fired::Map::deinit() {
	tileset.deinit();
}



void fired::Map::update() {
	render();
}



void fired::Map::render() {
	app->draw(*bgSprite);

	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 38; j++)
			tiles[i][j].render(app);
}



void fired::Map::checkPhys(fired::Phys *phys) {
	phys->velocity += phys->acceleration * frameClock;

	if (phys->velocity.x > PHYS_MAX_FALL) phys->velocity.x = PHYS_MAX_FALL;
	if (phys->velocity.y > PHYS_MAX_FALL) phys->velocity.y = PHYS_MAX_FALL;

	phys->onGround = false;
	phys->pos += phys->velocity * frameClock;
	phys->rect = sf::FloatRect(phys->pos, phys->size);

	sf::FloatRect intersection;
	sf::Vector2i  tiles_from((int)(phys->pos.x / TILE_SIZE), (int)(phys->pos.y / TILE_SIZE));
	sf::Vector2i  tiles_to((int)((phys->pos.x + phys->size.x) / TILE_SIZE), (int)((phys->pos.y + phys->size.y) / TILE_SIZE));


	for (int i = tiles_from.x; i <= tiles_to.x; i++) 
	for (int j = tiles_from.y; j <= tiles_to.y; j++) 
		if (tiles[i][j].isSolid())
			if (phys->rect.intersects(sf::FloatRect(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE), intersection)) {
				if (intersection.width > intersection.height) {
					if (phys->pos.y < j * TILE_SIZE) {
						phys->pos.y -= intersection.height;
						phys->velocity.y = 0;
						phys->onGround = true;
					} else {
						phys->pos.y += intersection.height;
						phys->velocity.y = 0;
					}
				} else {
					if (phys->pos.x < i * TILE_SIZE) {
						phys->pos.x -= intersection.width;
						phys->velocity.x = 0;
					} else {
						phys->pos.x += intersection.width;
						phys->velocity.x = 0;
					}
				}

				phys->rect = sf::FloatRect(phys->pos, phys->size);
			}

}
