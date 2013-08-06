#include "game.hpp"

//======================================================================


void fired::GUI::init(fired::Game *_game, fired::Camera *_cam, fired::Player *_player) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	cam      = _cam;
	player   = _player;

	barTex = new sf::Texture;
	barTex->loadFromFile("data/img/gui/world/guibar.tga");

	barSpr = new sf::Sprite;
	barSpr->setTexture(*barTex);

	healthTex = new sf::Texture;
	healthTex->loadFromFile("data/img/gui/world/health.tga");

	healthSpr = new sf::RectangleShape(sf::Vector2f(284, 27));
	healthSpr->setTexture(healthTex);
}

//======================================================================


void fired::GUI::deinit() {
	delete barSpr;
	delete barTex;
}

//======================================================================


void fired::GUI::update() {
	healthSpr->setScale(player->getChar()->getHpPercent(), 1);
	render();
}

//======================================================================


void fired::GUI::render() {
	healthSpr->setPosition(cam->getOffset() + sf::Vector2f(25, 25));
	app->draw(*healthSpr);

	barSpr->setPosition(cam->getOffset() + sf::Vector2f(20, 20));
	app->draw(*barSpr);
}
