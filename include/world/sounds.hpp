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
