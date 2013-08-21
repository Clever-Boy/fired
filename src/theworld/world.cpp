#include "game.hpp"

//======================================================================


fired::World::World() {
	game->setMusic("data/snd/themes/world.ogg");

	container = new fired::Container(this);
	cam       = new fired::Camera();
	map       = new fired::Map(cam, this);
	player    = new fired::Player(cam, map->getStartPos(), this);
	gui       = new fired::GUI(cam, player);

	cam->setMapSize(map->getSize());
	cam->setTrackObj(player->getPhys());

	chars.push_back(player->getChar());

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

	chars.clear();
}

//======================================================================


void fired::World::update() {
	checkControls();

	cam->update();
	map->update();
	player->update();

	checkShots();

	for (unsigned int i = 0; i < creatures.size(); creatures[i++]->update());

	for (unsigned int i = 0; i < shots.size();) {
		if (!shots[i]->update()) {
			delete shots[i];
			shots.erase(shots.begin() + i);
		} else
			i++;
	}

	for (unsigned int i = 0; i < particles.size();) {
		if (!particles[i]->update()) {
			delete particles[i];
			particles.erase(particles.begin() + i);
		} else
			i++;
	}

	for (unsigned int i = 0; i < chunks.size();)
		if (!chunks[i]->update()) {
			delete chunks[i];
			chunks.erase(chunks.begin() + i);
		} else {
			map->checkChunkPhys(chunks[i]);
			i++;
		}


	for (unsigned int i = 0; i < texts.size();) {
		if (!texts[i]->update()) {
			delete texts[i];
			texts.erase(texts.begin() + i);
		} else
			i++;
	}

	for (unsigned int i = 0; i < items.size(); items[i++]->render());
	for (unsigned int i = 0; i < chars.size(); i++) {
		if (!chars[i]->canPickup()) continue;

		for (unsigned int j = 0; j < items.size();)
			if (chars[i]->phys.rect.intersects(items[i]->phys.rect)) {
				chars[i]->pickup(items[i]);
				delete items[i];
				items.erase(items.begin() + i);
			} else
				j++;
	}


	for (unsigned int i = 0; i < creatures.size();) {
		if (creatures[i]->getChar()->isDead()) {
			for (unsigned int j = 0; j < chars.size(); j++)
				if (chars[j] == creatures[i]->getChar()) {
					chars.erase(chars.begin() + j);
					break;
				}

			delete creatures[i];
			creatures.erase(creatures.begin() + i);
			spawn(sf::Vector2f(2288, 560), "soldier");
		} else
			i++;
	}

	gui->update();
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

		for (unsigned int j = 0; j < chars.size(); j++) {
			if (chars[j]->checkShot(shots[i])) {
				delete shots[i];
				shots.erase(shots.begin() + i);
				deleted = true;
				break;
			}
		}

		if (deleted) continue;
		if (map->checkShot(shots[i])) {
			delete shots[i];
			shots.erase(shots.begin() + i);
			continue;
		}

		i++;
	}


	for (unsigned int i = 0; i < meleeShots.size(); i++)
		for (unsigned int j = 0; j < chars.size(); j++)
			chars[j]->checkMeleeShot(meleeShots[i]);

	deleteList(meleeShots);


	for (unsigned int i = 0; i < broadShots.size(); i++)
		for (unsigned int j = 0; j < chars.size(); j++)
			chars[j]->checkBroadShot(broadShots[i]);

	deleteList(broadShots);
}

//======================================================================


void fired::World::processEvent(sf::Event event) {
	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) game->stop();
}

//======================================================================


bool fired::World::isCharExists(fired::Character *character) {
	for (unsigned int i = 0; i < chars.size(); i++)
		if (character == chars[i]) return true;

	return false;
}

//======================================================================


void fired::World::spawn(sf::Vector2f pos, const char *creature) {
	creatures.push_back(new fired::Creature(cam, pos, this, getCreature(creature)));
	chars.push_back(creatures.back()->getChar());
}

//======================================================================


void fired::World::addBulletSplash(sf::Vector2f pos, sf::Vector2f direction) {
	particles.push_back(new fired::ParticleSystemSplash(pos, direction, this, sf::Color(239, 231, 145, 255), 2, 20, 0.3, 0, false));
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


void fired::World::addShot(sf::Vector2f pos, float angle, float speed, fired::Character *owner, sf::Sprite *sprite) {
	shots.push_back(new fired::Shot(pos, angle, speed, owner, sprite));
}

//======================================================================


void fired::World::addBroadShot(sf::FloatRect _shot, sf::Vector2f _normal, fired::Character *_owner) {
	broadShots.push_back(new fired::BroadShot(_shot, _normal, _owner));
}

//======================================================================


void fired::World::addMeleeShot(sf::Vector2f _pos, sf::Vector2f _direction, fired::Character *_owner) {
	meleeShots.push_back(new fired::MeleeShot(_pos, _direction, _owner));
}

//======================================================================


void fired::World::addText(sf::Vector2f pos, sf::Color color, int size, const char *text) {
	texts.push_back(new fired::FlyText(pos, color, size, text));
}
