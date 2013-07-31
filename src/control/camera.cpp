#include "game.hpp"

//======================================================================


void fired::Camera::init(fired::Game *_game, sf::Vector2i _mapSize) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	mapSize  = _mapSize;

	viewport = sf::FloatRect(0, 0, settings->window.width, settings->window.height);
	view.reset(viewport);
}

//======================================================================


void fired::Camera::update() {
	offset = sf::Vector2f(objToTrack->center.x - settings->window.width  / 2,
	                      objToTrack->center.y - settings->window.height / 2);

	if (offset.x < 0) offset.x = 0;
	if (offset.y < 0) offset.y = 0;

	if (offset.x > mapSize.x - settings->window.width ) offset.x = mapSize.x - settings->window.width;
	if (offset.y > mapSize.y - settings->window.height) offset.y = mapSize.y - settings->window.height;

	view.setCenter(offset + sf::Vector2f(settings->window.width / 2, settings->window.height / 2));
	app->setView(view);
}
