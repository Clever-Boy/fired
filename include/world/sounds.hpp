/***********************************************************************
     * File       : sounds.hpp
     * Created    : Jan 21, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __SOUNDS
#define __SOUNDS


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
