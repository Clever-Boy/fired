/***********************************************************************
     * File       : world_shot.cpp
     * Created    : Aug 26, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Shot
     * constructor

***********************************************************************/
fired::Shot::Shot(fired::Character *_owner, fired::World *_world) {
	owner     = _owner;
	pos       = owner->model->getBarrelPos();
	origin    = pos;
	angle     = owner->aiming;
	world     = _world;
	tracer    = NULL;
	farAway   = false;
	sprite    = owner->ammo->shotSprite;
	damage    = owner->getDamage();
	knockback = owner->getKnockback();
	leftToFly = owner->getRange();
	fraction  = owner->fraction;

	explosive       = owner->ammo->explosive;
	explosionRadius = owner->ammo->explosionRadius;

	angle += getRandomOffset(WEAPON_ZERO_ACCURACY * accuracyReduction(owner->stats.accuracy));
	if (owner->weapon->subtype == WEAPON_SUBTYPE_SHOTGUN) angle += getRandomOffset(WEAPON_ZERO_ACCURACY);

	velocity = sf::Vector2f(owner->weapon->speed * cos(angle), owner->weapon->speed * sin(angle));
	line = sf::VertexArray(sf::Lines, 2);
	line[0].color = sf::Color::White;
	line[1].color = sf::Color(205, 154, 0, 20);

	switch (owner->ammo->tracer) {
		case stNone:
			break;

		case stSmoke:
			tracer = new fired::ParticleSystemSmoke(sf::Vector2f(0,0), vSetLen(-velocity, 150), world, 25.0, &pos);
			world->particles.push_back(tracer);
			break;
	}
}



/***********************************************************************
     * Shot
     * constructor

***********************************************************************/
fired::Shot::~Shot() {
	if (tracer) tracer->stop();
}



/***********************************************************************
     * Shot
     * update

***********************************************************************/
bool fired::Shot::update() {
	leftToFly -= vLen(velocity) * frameClock;
	if (leftToFly < 0) return false;

	pos += velocity * frameClock;
	if (world->isPixelVisible(pos)) render();

	index = sf::Vector2i((int)(pos.x / TILE_SIZE), (int)(pos.y / TILE_SIZE));
	world->map->addIntensity(index, LIGHT_SHOT_INTENSITY, sf::Color::White);

	return true;
}



/***********************************************************************
     * Shot
     * render

***********************************************************************/
void fired::Shot::render() {
	if (sprite != NULL) {
		sprite->spr->setOrigin(sprite->size / 2.0f);
		sprite->spr->setRotation(angle * 180 / 3.14);
		sprite->spr->setPosition(pos);
		app->draw(*sprite->spr);
	} else {
		if (!farAway) farAway = vLen(pos - origin) > vLen(velocity * frameClock * 3.0f);

		line[0].position = pos;

		if (farAway) line[1].position = pos - velocity * frameClock * 2.0f;
		else         line[1].position = origin;

		app->draw(line);
	}
}



/***********************************************************************
     * BroadShot
     * constructor

***********************************************************************/
fired::BroadShot::BroadShot(sf::FloatRect _shot, sf::Vector2f _normal, fired::Character *_owner) {
	shot      = _shot;
	owner     = _owner;
	normal    = _normal;
	fraction  = owner->fraction;
	damage    = owner->getDamage();
	knockback = owner->getKnockback();
}



/***********************************************************************
     * MeleeShot
     * constructor

***********************************************************************/
fired::MeleeShot::MeleeShot(sf::Vector2f _pos, sf::Vector2f _direction, fired::Character *_owner) {
	pos       = _pos;
	owner     = _owner;
	direction = _direction;
	fraction  = owner->fraction;
	damage    = owner->getDamage();
	knockback = owner->getKnockback();
}
