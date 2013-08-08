#include "game.hpp"

//======================================================================


void fired::World::init(fired::Game *_game) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	game->setMusic("data/snd/themes/world.ogg");
	container.init(game, this);

	map.init(game, &cam, this);
	cam.init(game, map.getSize());
	player.init(game, &cam, map.getStartPos(), this);
	gui.init(game, &cam, &player);

	cam.setTrackObj(player.getPhys());
	spawn(sf::Vector2f(2288, 560), "soldier");
	spawn(sf::Vector2f(2388, 560), "soldier");
}

//======================================================================


void fired::World::deinit() {
	map.deinit();
	player.deinit();
	gui.deinit();
	container.deinit();

	for (int i = 0; i < shots.size(); i++) {
		shots[i]->deinit();
		delete shots[i];
	}

	for (int i = 0; i < particles.size(); i++) {
		particles[i]->deinit();
		delete particles[i];
	}

	for (int i = 0; i < creatures.size(); i++) {
		creatures[i]->deinit();
		delete creatures[i];
	}

	for (int i = 0; i < texts.size(); i++) {
		texts[i]->deinit();
		delete texts[i];
	}

	shots.clear();
	particles.clear();
	creatures.clear();
	texts.clear();
}

//======================================================================


void fired::World::update() {
	checkControls();

	cam.update();
	map.update();
	player.update();
	gui.update();


	for (int i = 0; i < creatures.size(); i++)
		creatures[i]->update();

	checkShots();

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

	for (int i = 0; i < texts.size();) {
		if (!texts[i]->update()) {
			texts[i]->deinit();
			delete texts[i];
			texts.erase(texts.begin() + i);
		} else
			i++;
	}

	for (int i = 0; i < creatures.size();) {
		if (creatures[i]->getChar()->isDead()) {
			creatures[i]->deinit();
			delete creatures[i];
			creatures.erase(creatures.begin() + i);
			spawn(sf::Vector2f(2288, 560), "soldier");
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


void fired::World::checkShots() {
	sf::Vector2f c, n;
	bool deleted;

	for (int i = 0; i < shots.size();) {
		deleted = false;
		for (int j = 0; j < creatures.size(); j++) {
			if (creatures[j]->getChar()->checkShot(shots[i])) {
				shots[i]->deinit();
				delete shots[i];
				shots.erase(shots.begin() + i);

				deleted = true;
			}
			if (deleted) break;
		}
		if (!deleted) i++;
	}

	for (int i = 0; i < shots.size();) {
		if (map.checkShot(shots[i])) {
			shots[i]->deinit();
			delete shots[i];
			shots.erase(shots.begin() + i);
		} else
			i++;
	}
}

//======================================================================


void fired::World::processEvent(sf::Event event) {
	return;
}

//======================================================================


void fired::World::spawn(sf::Vector2f pos, const char *creature) {
	creatures.push_back(new fired::Creature);
	creatures.back()->init(game, &cam, pos, this, getCreature(creature));
}

//======================================================================


void fired::World::addBulletSplash(sf::Vector2f pos, sf::Vector2f direction) {
	fired::ParticleSystemSplash *ps = new fired::ParticleSystemSplash;
	ps->init(pos, direction, sf::Color(255, 155, 0, 255), 2);
	particles.push_back(ps);
}

//======================================================================


void fired::World::addBloodSplash(sf::Vector2f pos, sf::Vector2f direction) {
	fired::ParticleSystemSplash *ps = new fired::ParticleSystemSplash;
	ps->init(pos, direction, sf::Color(150, 0, 0, 155), 3);
	particles.push_back(ps);
}

//======================================================================


void fired::World::addShot(sf::Vector2f pos, float angle, float speed, fired::Character *owner) {
	shots.push_back(new fired::Shot);
	shots.back()->init(pos, angle, speed, owner);
}

//======================================================================


void fired::World::addText(sf::Vector2f pos, sf::Color color, int size, const char *text) {
	texts.push_back(new fired::FlyText);
	texts.back()->init(game, pos, color, size, text);
}
