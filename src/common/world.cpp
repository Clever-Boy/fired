#include "game.hpp"

//======================================================================


void fired::World::init(fired::Game *_game) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	game->setMusic("data/snd/themes/world.ogg");

	weapons.push_back(new fired::BaseWeapon);
	weapons.back()->init();

	map.init(game, &cam, this);
	cam.init(game, map.getSize());
	player.init(game, &cam, map.getStartPos(), this);

	cam.setTrackObj(player.getPhys());
}

//======================================================================


void fired::World::deinit() {
	map.deinit();
	player.deinit();

	for (int i = 0; i < shots.size(); i++) {
		shots[i]->deinit();
		delete shots[i];
	}

	for (int i = 0; i < particles.size(); i++) {
		particles[i]->deinit();
		delete particles[i];
	}

	for (int i = 0; i < weapons.size(); i++) {
		delete weapons[i];
	}
}

//======================================================================


void fired::World::update() {
	checkControls();
	map.checkPhys(player.getPhys());

	for (int i = 0; i < shots.size();) {
		if (map.checkShot(shots[i])) {
			shots[i]->deinit();
			delete shots[i];
			shots.erase(shots.begin() + i);
		} else
			i++;
	}

	cam.update();
	map.update();
	player.update();


	for (int i = 0; i < shots.size(); i++)
		shots[i]->update(app);

	for (int i = 0; i < particles.size();) {
		if (!particles[i]->update(app)) {
			particles[i]->deinit();
			delete particles[i];
			particles.erase(particles.begin() + i);
		} else
			i++;
	}
}

//======================================================================


void fired::World::checkControls() {
	player.checkControls();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) game->stop();
}

//======================================================================


void fired::World::processEvent(sf::Event event) {
	return;
}

//======================================================================


void fired::World::addBulletSplash(sf::Vector2f pos, sf::Vector2f direction) {
	fired::ParticleSystemSplash *ps = new fired::ParticleSystemSplash;
	ps->init(pos, direction, sf::Color(255, 155, 0, 255));
	particles.push_back(ps);
}

//======================================================================


void fired::World::addShot(sf::Vector2f pos, float angle, float speed, fired::Character *owner) {
	shots.push_back(new fired::Shot);
	shots.back()->init(pos, angle, speed, owner);
}
