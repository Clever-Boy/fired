/***********************************************************************
     * File       : resources.cpp
     * Created    : Aug 02, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * Resources
     * constructor

***********************************************************************/
fired::Resources::Resources() {
	sounds.explosion_buf = new sf::SoundBuffer();
	sounds.explosion_buf->loadFromFile("data/snd/misc/explosion.wav");

	sounds.explosion = new sf::Sound();
	sounds.explosion->setBuffer(*sounds.explosion_buf);
	sounds.explosion->setVolume(settings->volume.sound);
}



/***********************************************************************
     * Resources
     * destructor

***********************************************************************/
fired::Resources::~Resources() {
	delete sounds.explosion;
	delete sounds.explosion_buf;
}
