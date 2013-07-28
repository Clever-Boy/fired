#include "game.hpp"


void fired::Character::init(fired::Game *_game, b2World *_physWorld) {
	game      = _game;
	settings  = game->getSettings();
	app       = game->getApp();
	physWorld = _physWorld;

	phys.pos          = sf::Vector2f(384, 2360);
	phys.size         = sf::Vector2f(32, 48);
	phys.onGround     = false;

	b2BodyDef      bodyDef;
	b2PolygonShape shapeDef;
	b2FixtureDef   fixtureDef;

	bodyDef.position = b2Vec2(toPhys(phys.pos.x), toPhys(phys.pos.y));
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;

	shapeDef.SetAsBox(toPhys(phys.size.x / 2), toPhys(phys.size.y / 2));
	fixtureDef.density = 1;
	fixtureDef.friction = 0.7;
	fixtureDef.shape = &shapeDef;

	body = physWorld->CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);

	baseStats.speed  = 220.0;
	baseStats.accel  = 1200.0;
	baseStats.jump   = 520.0;
	baseStats.aiming = 100.0;

	isMoving  = false;
	direction = 1;

	texture = new sf::Texture();
	sprite  = new sf::Sprite();

	texture->loadFromFile("data/img/chars/player.tga");
	sprite->setTexture(*texture);
	sprite->setOrigin(phys.size.x / 2, phys.size.y / 2);
	texture->setSmooth(true);
}



void fired::Character::deinit() {
	delete sprite;
	delete texture;
}



void fired::Character::update() {
	phys.pos = sf::Vector2f(fromPhys(body->GetPosition().x), fromPhys(body->GetPosition().y));
	render();
}



void fired::Character::render() {
	sprite->setPosition(phys.pos);
	game->getApp()->draw(*sprite);
}



void fired::Character::moveLeft() {
	direction = -1;
	isMoving  = true;
}



void fired::Character::moveRight() {
	direction = 1;
	isMoving  = true;
}



void fired::Character::jump() {
	if (phys.onGround) return;
}
