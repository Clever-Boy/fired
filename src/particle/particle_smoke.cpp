/***********************************************************************
     * File       : particle_smoke.cpp
     * Created    : Feb 12, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * ParticleSystemSmoke
     * constructor

***********************************************************************/
fired::ParticleSystemSmoke::ParticleSystemSmoke(sf::Vector2f pos, sf::Vector2f direction, fired::World *world, float size, sf::Vector2f *follow = NULL) : fired::ParticleSystemSpray(pos, direction, world, sf::Color::White, size, 0.05, 0.3, 1.5, false, follow) {
	sprite->setTexture(resources->sprites.smokeTex);
	sprite->setTextureRect(sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(resources->sprites.smokeTex->getSize())));

	accel = sf::Vector2f(0, -PHYS_GRAVITY / 2);
}
