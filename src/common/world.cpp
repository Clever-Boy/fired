#include "game.hpp"

//======================================================================


fired::World::World(fired::Game *_game) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	game->setMusic("data/snd/themes/world.ogg");

	container = new fired::Container(game, this);
	cam       = new fired::Camera(game);
	map       = new fired::Map(game, cam, this);
	player    = new fired::Player(game, cam, map->getStartPos(), this);
	gui       = new fired::GUI(game, cam, player);

	cam->setMapSize(map->getSize());
	cam->setTrackObj(player->getPhys());

	spawn(sf::Vector2f(2288, 560), "soldier");
	spawn(sf::Vector2f(2388, 560), "soldier");
}

//======================================================================


fired::World::~World() {
	delete player;
	delete map;
	delete gui;
	delete cam;
	delete container;

	deleteList(shots);
	deleteList(particles);
	deleteList(creatures);
	deleteList(texts);
	deleteList(chunks);
}

//======================================================================


void fired::World::update() {
	checkControls();

	cam->update();
	map->update();
	player->update();
	gui->update();

	for (unsigned int i = 0; i < creatures.size(); creatures[i++]->update());
	checkShots();
	for (unsigned int i = 0; i < shots.size(); shots[i++]->update(app));


	for (unsigned int i = 0; i < particles.size();) {
		if (!particles[i]->update(app)) {
			delete particles[i];
			particles.erase(particles.begin() + i);
		} else
			i++;
	}

	for (unsigned int i = 0; i < chunks.size();) {
		map->checkChunkPhys(chunks[i]);
		if (!chunks[i]->update(app)) {
			delete chunks[i];
			chunks.erase(chunks.begin() + i);
		} else
			i++;
	}

	for (unsigned int i = 0; i < texts.size();) {
		if (!texts[i]->update()) {
			delete texts[i];
			texts.erase(texts.begin() + i);
		} else
			i++;
	}

	for (unsigned int i = 0; i < creatures.size();) {
		if (creatures[i]->getChar()->isDead()) {
			delete creatures[i];
			creatures.erase(creatures.begin() + i);
			spawn(sf::Vector2f(2288, 560), "soldier");
		} else
			i++;
	}
}

//======================================================================


void fired::World::checkControls() {
	player->checkControls();
}

//======================================================================


void fired::World::checkShots() {
	sf::Vector2f c, n;
	bool deleted;

	for (unsigned int i = 0; i < shots.size();) {
		deleted = false;
		for (unsigned int j = 0; j < creatures.size(); j++) {
			if (creatures[j]->getChar()->checkShot(shots[i])) {
				delete shots[i];
				shots.erase(shots.begin() + i);

				deleted = true;
			}
			if (deleted) break;
		}
		if (!deleted) i++;
	}

	for (unsigned int i = 0; i < shots.size();) {
		if (map->checkShot(shots[i])) {
			delete shots[i];
			shots.erase(shots.begin() + i);
		} else
			i++;
	}
}

//======================================================================


void fired::World::processEvent(sf::Event event) {
	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) game->stop();
}

//======================================================================


void fired::World::spawn(sf::Vector2f pos, const char *creature) {
	creatures.push_back(new fired::Creature(game, cam, pos, this, getCreature(creature)));
}

//======================================================================


void fired::World::addBulletSplash(sf::Vector2f pos, sf::Vector2f direction) {
	particles.push_back(new fired::ParticleSystemSplash(pos, direction, this, sf::Color(255, 155, 0, 255), 2, 20, 0.3, 0, false));
}

//======================================================================


void fired::World::addBloodSplash(sf::Vector2f pos, sf::Vector2f direction, int bloodCount) {
	particles.push_back(new fired::ParticleSystemSplash(pos, direction, this, sf::Color(150, 0, 0, 155), 7, bloodCount, 17.0, 0.5, true));
}

//======================================================================


void fired::World::addChunk(fired::Bodypart *bodyPart, float scale, sf::Vector2f position, sf::Vector2f speed) {
	chunks.push_back(new fired::Chunk(bodyPart, scale, position, speed));
}

//======================================================================


void fired::World::addShot(sf::Vector2f pos, float angle, float speed, fired::Character *owner) {
	shots.push_back(new fired::Shot(pos, angle, speed, owner));
}

//======================================================================


void fired::World::addText(sf::Vector2f pos, sf::Color color, int size, const char *text) {
	texts.push_back(new fired::FlyText(game, pos, color, size, text));
}
