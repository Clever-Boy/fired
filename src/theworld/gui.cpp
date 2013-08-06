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
}

//======================================================================


void fired::GUI::deinit() {
	delete barSpr;
	delete barTex;
}

//======================================================================


void fired::GUI::update() {
	render();
}

//======================================================================


void fired::GUI::render() {
	barSpr->setPosition(cam->getOffset() + sf::Vector2f(20, 20));
	app->draw(*barSpr);
}
