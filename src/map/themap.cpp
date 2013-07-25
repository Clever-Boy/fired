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
