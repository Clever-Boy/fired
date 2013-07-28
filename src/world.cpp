#include "game.hpp"


void fired::World::init(fired::Game *_game) {
	game      = _game;
	settings  = game->getSettings();
	app       = game->getApp();
	physWorld = new b2World(b2Vec2(0, 9.8));

	map.init(game, &cam, physWorld);
	cam.init(game);
	player.init(game, &cam, physWorld);

	cam.setTrackObj(player.getPhys());
}



void fired::World::deinit() {
	map.deinit();
	player.deinit();

	delete physWorld;
}



void fired::World::update() {
	checkControls();

	physWorld->Step(frameClock, 8, 3);
	cam.update();
	map.update();
	player.update();
}



void fired::World::checkControls() {
	player.checkControls();
}



void fired::World::processEvent(sf::Event event) {
	return;
}
