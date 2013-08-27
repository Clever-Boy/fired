#include "game.hpp"

//======================================================================


fired::World::World(fired::Mouse *_mouse) {
	game->setMusic("data/snd/themes/world.ogg");
	paused = false;
	mouse  = _mouse;
	state  = wsNormal;

	container = new fired::Container(this);
	cam       = new fired::Camera();
	map       = new fired::Map(cam, this);
	crosshair = new fired::Crosshair(cam);
	player    = new fired::Player(cam, map->getStartPos(), crosshair, this);
	gui       = new fired::GUI(player);

	inventoryWin = new fired::InventoryWindow(player->getChar());
	exchangeWin  = new fired::ExchangeWindow(player->getChar());

	cam->setMapSize(map->getSize());
	cam->setTrackObj(player->getPhys());

	chars.push_back(player->getChar());

	spawn(sf::Vector2f(2288, 560), "soldier");
	spawn(sf::Vector2f(2388, 560), "soldier");
}

//======================================================================


fired::World::~World() {
	delete player;
	delete crosshair;
	delete map;
	delete gui;
	delete cam;
	delete container;

	delete inventoryWin;
	delete exchangeWin;

	deleteList(shots);
	deleteList(meleeShots);
	deleteList(broadShots);
	deleteList(particles);
	deleteList(creatures);
	deleteList(texts);
	deleteList(chunks);

	chars.clear();
}

//======================================================================


void fired::World::update() {
	preUpdateState();

	cam->update();
	map->update();
	player->update();

	checkShots();
	checkPhys();
	checkCreatures();
	checkItems();

	updateList(chunks);
	updateList(shots);
	updateList(particles);
	updateList(texts);

	postUpdateState();
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


void fired::World::checkCreatures() {
	for (unsigned int i = 0; i < creatures.size();) {
		creatures[i]->update();

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
}

//======================================================================


void fired::World::checkPhys() {
	for (unsigned int i = 0; i < chars.size() ; map->checkPhys(&chars[i]->phys, chars[i]), i++);
	for (unsigned int i = 0; i < chunks.size(); map->checkPhys(&chunks[i++]->phys, NULL));
	for (unsigned int i = 0; i < items.size() ; map->checkPhys(&items[i++]->phys, NULL));
}

//======================================================================


void fired::World::checkItems() {
	for (unsigned int i = 0; i < items.size(); i++) {
		items[i]->update();

		for (unsigned int j = 0; j < chars.size(); j++) {
			if ( chars[j]->isDead()) continue;
			if (!chars[j]->canPickup(items[i]->item)) continue;

			if (chars[j]->phys.rect.intersects(items[i]->phys.rect)) {
				chars[j]->pickup(items[i]->item);

				delete items[i];
				items.erase(items.begin() + i);
				i++;
				break;
			}
		}
	}
}

//======================================================================


void fired::World::processEvent(sf::Event event) {
	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
		if      (state == wsNormal)    game->stop();
		else if (state == wsInventory) state = wsNormal;
		else if (state == wsExchange)  state = wsNormal;
	}


	if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::I)) {
		if (state != wsInventory) state = wsInventory;
		else                      state = wsNormal;
	}


	if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
		if (state == wsInventory) inventoryWin->click(mouse->getPos());
		if (state == wsExchange)  exchangeWin->click(mouse->getPos());
	}
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


void fired::World::interact(fired::Character *owner) {
	fired::MapObject *obj = map->checkInteraction(owner);
	if (obj == NULL) return;

	if (obj->type == moCollector) {
		exchangeWin->init((fired::MapObjectCollector*)obj);
		state = wsExchange;
	}
}

//======================================================================


void fired::World::preUpdateState() {
	if (paused) frameClock = 0.0f;

	switch (state) {
		case wsNormal:
			player->checkControls();
			break;

		case wsInventory:
			frameClock = 0.0f;
			break;

		case wsExchange:
			frameClock = 0.0f;
			break;
	}
}

//======================================================================


void fired::World::postUpdateState() {
	switch (state) {
		case wsNormal:
			crosshair->update(player->getChar()->getStats()->aimrange);
			cam->reset();
			gui->update();
			break;

		case wsInventory:
			cam->reset();
			gui->update();
			inventoryWin->update(mouse->getPos());
			mouse->update();
			break;

		case wsExchange:
			cam->reset();
			gui->update();
			exchangeWin->update(mouse->getPos());
			mouse->update();
			break;
	}
}
