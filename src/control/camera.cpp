#include "game.hpp"


void fired::Camera::init(fired::Game *_game) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	viewport = sf::FloatRect(0, 0, settings->window.width, settings->window.height);
	view.reset(viewport);
}



void fired::Camera::update() {
	view.setCenter(objToTrack->rect.left + objToTrack->rect.width / 2, objToTrack->rect.top + objToTrack->rect.height / 2);
	app->setView(view);
}
