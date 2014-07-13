/***********************************************************************
     * File       : world_sound.cpp
     * Created    : Jan 21, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * GameSound
     * constructor

***********************************************************************/
fired::GameSound::GameSound(const char *filename, const char *_name) {
	strcpy(name, _name);

	buf = new sf::SoundBuffer();
	buf->loadFromFile(filename);

	snd = new sf::Sound();
	snd->setBuffer(*buf);
	snd->setVolume(settings->volume.sound);
	snd->setMinDistance(SOUND_MINDISTANCE);
	snd->setAttenuation(SOUND_ATTENUATION);
}



/***********************************************************************
     * GameSound
     * destructor

***********************************************************************/
fired::GameSound::~GameSound() {
	delete buf;
	delete snd;
}
