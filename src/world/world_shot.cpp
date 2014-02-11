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
	pos       = owner->phys.center;
	angle     = owner->aiming;
	world     = _world;

	sprite    = owner->weapon->shotSprite;
	damage    = owner->getDamage();
	knockback = owner->getKnockback();
	leftToFly = owner->getRange();
	fraction  = owner->fraction;

	explosive       = owner->weapon->explosive;
	explosionRadius = owner->weapon->explosionRadius;

	velocity = sf::Vector2f(owner->weapon->speed * cos(angle), owner->weapon->speed * sin(angle));
	line = sf::VertexArray(sf::Lines, 2);
	line[0].color = sf::Color::White;
	line[1].color = sf::Color(141, 152, 141, 50);

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
		line[0].position = pos;
		line[1].position = pos - velocity * frameClock * 2.0f;
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