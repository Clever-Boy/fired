/***********************************************************************
     * File       : world_sound.hpp
     * Created    : Jan 21, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __WORLD_SOUND
#define __WORLD_SOUND


namespace fired {
	struct GameSound {
		char             name[64];
		sf::SoundBuffer *buf;
		sf::Sound       *snd;


		 GameSound(const char *filename, const char *_name);
		~GameSound();
	};
}

#endif
