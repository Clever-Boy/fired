/***********************************************************************
     * File       : world_base.cpp
     * Created    : Jul 24, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * World
     * constructor

***********************************************************************/
fired::World::World(fired::Mouse *_mouse) {
	game->setMusic("data/snd/themes/world.ogg");
	paused = false;
	mouse  = _mouse;
	state  = wsNormal;

	cam       = new fired::Camera();
	map       = new fired::Map(cam, this);
	crosshair = new fired::Crosshair(cam);
	player    = new fired::Player(cam, map->startPos, crosshair, this);
	gui       = new fired::GUI(player->character);

	inventoryWin = new fired::InventoryWindow(player->character, this);
	exchangeWin  = new fired::ExchangeWindow(player->character, this);
	characterWin = new fired::CharacterWindow(player->character);
	menuWin      = new fired::MenuWindow(this);

	cam->mapSize    = sf::Vector2i(map->sizeX * TILE_SIZE, map->sizeY * TILE_SIZE);
	cam->objToTrack = &player->character->phys;
	cam->update();

	map->setWeather();
	chars.push_back(player->character);

	spawnRate = 4.0f;
	spawnLeft = spawnRate;
	spawnMax  = 7;
}



/***********************************************************************
     * World
     * destructor

***********************************************************************/
fired::World::~World() {
	delete player;
	delete crosshair;
	delete map;
	delete gui;
	delete cam;

	delete inventoryWin;
	delete exchangeWin;
	delete characterWin;
	delete menuWin;

	deleteList(shots);
	deleteList(meleeShots);
	deleteList(broadShots);
	deleteList(particles);
	deleteList(creatures);
	deleteList(texts);
	deleteList(chunks);
	deleteList(explosions);

	chars.clear();
}



/***********************************************************************
     * World
     * update

***********************************************************************/
void fired::World::update() {
	preUpdateState();
	cam->update();
	map->update();
	player->update();

	checkShots();
	checkCreatures();
	checkPhys();
	checkItems();
	checkSpawns();

	updateList(chunks);
	updateList(shots);
	updateList(particles);
	updateList(explosions);
	map->light();
	updateList(texts);

	postUpdateState();
}



/***********************************************************************
     * World
     * checkShots

***********************************************************************/
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



/***********************************************************************
     * World
     * checkCreatures

***********************************************************************/
void fired::World::checkCreatures() {
	for (unsigned int i = 0; i < creatures.size();) {
		creatures[i]->update();

		if (creatures[i]->character->dead) {
			for (unsigned int j = 0; j < chars.size(); j++)
				if (chars[j] == creatures[i]->character) {
					chars.erase(chars.begin() + j);
					break;
				}

			delete creatures[i];
			creatures.erase(creatures.begin() + i);
		} else
			i++;
	}
}



/***********************************************************************
     * World
     * checkPhys

***********************************************************************/
void fired::World::checkPhys() {
	for (unsigned int i = 0; i < chars.size() ; map->checkPhys(&chars[i]->phys   , chars[i], PHYS_TUNNEL_TIME), i++);
	for (unsigned int i = 0; i < chunks.size(); map->checkPhys(&chunks[i++]->phys, NULL    , PHYS_TUNNEL_CHUNK));
	for (unsigned int i = 0; i < items.size() ; map->checkPhys(&items[i++]->phys , NULL    , PHYS_TUNNEL_CHUNK));
}



/***********************************************************************
     * World
     * checkSpawns

***********************************************************************/
void fired::World::checkSpawns() {
	if (chars.size() >= spawnMax) return;

	spawnLeft -= frameClock;
	if (spawnLeft <= 0) {
		spawnLeft = spawnRate;
		map->spawn(player->character->phys.pos);
	}
}



/***********************************************************************
     * World
     * checkItems

***********************************************************************/
void fired::World::checkItems() {
	for (unsigned int i = 0; i < items.size(); i++) {
		items[i]->update();

		for (unsigned int j = 0; j < chars.size(); j++) {
			if ( chars[j]->dead) continue;

			if (chars[j]->phys.rect.intersects(items[i]->phys.rect)) {
				if (!chars[j]->canPickup(&items[i]->item)) continue;
				chars[j]->pickup(&items[i]->item);

				if (!items[i]->item.count) {
					delete items[i];
					items.erase(items.begin() + i);
					i++;
					break;
				}
			}
		}
	}
}



/***********************************************************************
     * World
     * processEvent

***********************************************************************/
void fired::World::processEvent(sf::Event event) {
	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
		if      (state == wsNormal)    state = wsMenu;
		else if (state == wsInventory) state = wsNormal;
		else if (state == wsExchange)  state = wsNormal;
		else if (state == wsCharacter) state = wsNormal;
		else if (state == wsMenu)      state = wsNormal;
	}


	if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::I)) {
		if (state != wsInventory) state = wsInventory;
		else                      state = wsNormal;
	}


	if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::C)) {
		if (state != wsCharacter) state = wsCharacter;
		else                      state = wsNormal;
	}


	if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
		if (state == wsCharacter) characterWin->click(mouse->pos);
		if (state == wsInventory) inventoryWin->click(mouse->pos);
		if (state == wsExchange)  exchangeWin->click(mouse->pos);
	}


	if ((event.type == sf::Event::MouseButtonReleased) && (event.mouseButton.button == sf::Mouse::Left)) {
		if (state == wsMenu)      menuWin->click(mouse->pos);
	}


	if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Right)) {
		if (state == wsInventory) inventoryWin->clickRight(mouse->pos);
		if (state == wsExchange)  exchangeWin->clickRight(mouse->pos);
	}
}



/***********************************************************************
     * World
     * isCharExists

***********************************************************************/
bool fired::World::isCharExists(fired::Character *character) {
	for (unsigned int i = 0; i < chars.size(); i++)
		if (character == chars[i]) return true;

	return false;
}



/***********************************************************************
     * World
     * spawn

***********************************************************************/
void fired::World::spawn(sf::Vector2f pos, fired::BaseCreature *creature) {
	creatures.push_back(new fired::Creature(cam, pos, this, creature));
	chars.push_back(creatures.back()->character);
}



/***********************************************************************
     * World
     * interact

***********************************************************************/
void fired::World::interact(fired::Character *owner) {
	fired::MapObject *obj = map->checkInteraction(owner);
	if (obj == NULL) return;

	if (obj->type == moCollector) {
		exchangeWin->init((fired::MapObjectCollector*)obj);
		state = wsExchange;
	}
}



/***********************************************************************
     * World
     * addExplosion

***********************************************************************/
void fired::World::addExplosion(sf::Vector2f pos, float radius, float life, float knockback, int damage, fired::Character *owner, int fraction) {
	explosions.push_back(new fired::Explosion(pos, radius, life));
	map->addExplosion(pos, radius, life * 2.0f);

	sf::Vector2f knock;
	float len;


	for (unsigned int i = 0; i < chunks.size(); i++) {
		knock = chunks[i]->phys.center - pos;
		len = vLen(knock);

		if (len <= radius && len > 0) chunks[i]->phys.velocity += vSetLen(knock, knockback * (radius - len) / radius);
	}

	for (unsigned int i = 0; i < chars.size(); i++) {
		knock = chars[i]->phys.center - pos;
		len = vLen(knock);

		if (len <= radius && len > 0) {
			chars[i]->phys.velocity += vSetLen(knock, knockback * (radius - len) / radius);

			if (chars[i]->isEnemy(fraction))
				chars[i]->damage(damage * (radius - len) / radius, pos, knockback * (radius - len) / radius, owner);
		}
	}

	for (unsigned int i = 0; i < items.size(); i++) {
		knock = items[i]->phys.center - pos;
		len = vLen(knock);

		if (len <= radius && len > 0) items[i]->phys.velocity += vSetLen(knock, knockback * (radius - len) / radius);
	}
}



/***********************************************************************
     * World
     * preUpdateState

***********************************************************************/
void fired::World::preUpdateState() {
	if (paused) frameClock = 0.0f;

	switch (state) {
		case wsNormal:
			player->checkControls();
			break;

		case wsInventory:
		case wsExchange:
		case wsCharacter:
		case wsMenu:
			frameClock = 0.0f;
			break;
	}
}



/***********************************************************************
     * World
     * postUpdateState

***********************************************************************/
void fired::World::postUpdateState() {
	switch (state) {
		case wsNormal:
			crosshair->update(player->character->stats.aimrange);
			cam->reset();
			gui->update();
			break;

		case wsInventory:
			cam->reset();
			gui->update();
			inventoryWin->update(mouse->pos);
			mouse->update();
			break;

		case wsExchange:
			cam->reset();
			gui->update();
			exchangeWin->update(mouse->pos);
			mouse->update();
			break;

		case wsCharacter:
			cam->reset();
			gui->update();
			characterWin->update();
			mouse->update();
			break;

		case wsMenu:
			cam->reset();
			gui->update();
			menuWin->update(mouse->pos);
			mouse->update();
			break;
	}
}
