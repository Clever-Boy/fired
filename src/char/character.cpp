#include "game.hpp"


void fired::Character::init(fired::Game *_game) {
	game     = _game;
	settings = game->getSettings();
	app      = game->getApp();

	phys.pos          = sf::Vector2f(384, 0);
	phys.velocity     = sf::Vector2f(0, 0);
	phys.acceleration = sf::Vector2f(0, PHYS_GRAVITY);
	phys.size         = sf::Vector2f(32, 48);

	baseStats.speed = 120.0;

	texture = new sf::Texture();
	sprite  = new sf::Sprite();

	texture->loadFromFile("data/img/chars/player.tga");
	sprite->setTexture(*texture);
	texture->setSmooth(true);
}



void fired::Character::deinit() {
	delete sprite;
	delete texture;
}



void fired::Character::update() {
	render();
}



void fired::Character::render() {
	sprite->setPosition(phys.pos);
	game->getApp()->draw(*sprite);
}



void fired::Character::moveLeft() {
	phys.pos.x -= frameClock * baseStats.speed;
}


void fired::Character::moveRight() {
	phys.pos.x += frameClock * baseStats.speed;
}
