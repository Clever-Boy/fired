#include "game.hpp"

//======================================================================


void fired::BaseWeapon::init(fired::Game *_game, fired::Character *_owner, fired::World *_world) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();
	owner    = _owner;
	world    = _world;

	tex = new sf::Texture;
	tex->loadFromFile("data/img/world/models/weapons/amp.tga");

	spr = new sf::Sprite;
	spr->setTexture(*tex);
	spr->setOrigin(tex->getSize().x / 2, tex->getSize().y / 2);
}

//======================================================================


void fired::BaseWeapon::deinit() {
	delete spr;
	delete tex;
}

//======================================================================


void fired::BaseWeapon::update() {
	render();
}

//======================================================================


void fired::BaseWeapon::render() {
	spr->setPosition(owner->phys.center + sf::Vector2f(0, 4));
	app->draw(*spr);
}

//======================================================================


void fired::Weapon::init(fired::BaseWeapon *_weapon) {
	baseWeapon = _weapon;
}

//======================================================================


void fired::Weapon::deinit() {
	return;
}

//======================================================================


void fired::Weapon::update() {
	render();
}

//======================================================================


void fired::Weapon::render() {
	baseWeapon->render();
}
